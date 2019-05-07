#include <rudp.h>

t_packet_out	*resend(t_rudp *rudp, t_rudp_peer *peer, t_packet_out *pack_out,
	Uint32 tick)
{
	if (pack_out->mode.delay + pack_out->tick_queued > tick)
		return (pack_out);
	if (tick >= pack_out->last_sent + RUDP_RESEND_TIMEOUT)
	{
		pack_out->last_sent = tick;
		SDLNet_UDP_Send(rudp->sender_socket, -1, pack_out->packet);
		if (!pack_out->mode.need_ack)
			return (remove_packet(&peer->window, pack_out));
	}
	else if (pack_out->mode.can_timeout
	&& tick - pack_out->tick_queued > pack_out->mode.timeout)
	{
		if (pack_out->mode.on_timeout != NULL)
			pack_out->mode.on_timeout(rudp, peer, pack_out,
				pack_out->mode.on_timeout_data);
		return (remove_packet(&peer->window, pack_out));
	}
	return (pack_out->next);
}

int		timedout(t_rudp *rudp, t_rudp_peer *peer, Uint32 tick)
{
	if (peer->last_recv + RUDP_CONNECTION_TIMEOUT < tick)
	{
		peer_switch_state(rudp, peer, RUDP_STATE_CLOSED);
		return (1);
	}
	return (0);
}

int		sender_thread(t_rudp *rudp)
{
	Uint32			i;
	Uint32			j;
	t_packet_out	*pack_out;
	Uint32			tick;

	while (rudp->running)
	{
		i = (Uint32)-1;
		tick = SDL_GetTicks();
		while (++i < rudp->nb_connections)
			if (!SDL_TryLockMutex(rudp->peers[i].mutex))
			{
				if (rudp->peers[i].state != RUDP_STATE_CLOSED
					&& !timedout(rudp, &rudp->peers[i], tick))
				{
					j = (Uint32)-1;
					pack_out = rudp->peers[i].window.queue;
					while (++j < RUDP_MAX_WINDOW && pack_out != NULL)
						pack_out = resend(rudp, &rudp->peers[i], pack_out, tick);
				}
				SDL_UnlockMutex(rudp->peers[i].mutex);
			}
		SDL_Delay(1);
	}
	return (0);
}
