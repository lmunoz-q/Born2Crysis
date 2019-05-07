#include <rudp.h>

/*
** search the message bound to the ack to flag it as accepted
** if the ack is not catch by any msg, it is ignored
*/

int		received_ack(t_rudp *rudp, t_rudp_peer *peer, Uint32 ack)
{
	int				i;
	t_packet_out	*out;

	i = -1;
	out = peer->window.queue;
	peer->last_recv = SDL_GetTicks();
	while (++i < RUDP_MAX_WINDOW && out != NULL)
	{
		if (out->mode.need_ack && ack == out->mode.ack)
		{
			if (out->mode.on_ack != NULL)
				out->mode.on_ack(rudp, peer, out, out->mode.on_ack_data);
			if (peer->state != RUDP_STATE_CLOSED)
				remove_packet(&peer->window, out);
			break;
		}
		out = out->next;
	}
	return (0);
}
