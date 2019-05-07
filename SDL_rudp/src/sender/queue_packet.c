#include <rudp.h>

static inline void	i_queue(t_rudp_window *win, t_packet_out *out)
{
	t_packet_out	*tmp;

	out->next = NULL;
	if (win->queue != NULL)
	{
		tmp = win->queue;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = out;
		out->prev = tmp;
	}
	else
	{
		win->queue = out;
		out->prev = NULL;
	}
}

/*
** packet that do not need ack and aren't delayed are sent right away
** if there is place in the window, store the packet imediately
** otherwise queue the packet to be sent when the window is less full
*/

t_packet_out		*queue_packet(t_rudp *rudp, t_rudp_peer *peer,
								UDPpacket *packet, t_queue_mode mode)
{
	t_packet_out	*out;
	int				i;

	if (mode.need_ack || mode.delay > 0)
	{
		i = -1;
		if ((out = SDL_malloc(sizeof(t_packet_out))) == NULL)
		{
			rudp->errno = RUDP_ERROR_NO_MEMORY;
			return (NULL);
		}
		*out = (t_packet_out){.mode = mode, .packet = packet,
			.next = NULL, .tick_queued = SDL_GetTicks(),
			.last_sent = SDL_GetTicks() - RUDP_RESEND_TIMEOUT};
		i_queue(&peer->window, out);
		rudp->errno = RUDP_ERROR_OK;
		return (out);
	}
	i = SDLNet_UDP_Send(rudp->sender_socket, -1, packet);
	SDL_free(packet);
	rudp->errno = i == 1 ? RUDP_ERROR_OK : RUDP_ERROR_SDLNET;
	return (NULL);
}
