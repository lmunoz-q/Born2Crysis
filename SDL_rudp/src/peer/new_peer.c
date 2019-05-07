#include <rudp.h>

t_rudp_peer	*new_peer(t_rudp *rudp, IPaddress target)
{
	Uint32		i;
	t_rudp_peer	*out;

	i = (Uint32)-1;
	while (++i < rudp->nb_connections)
		if (rudp->peers[i].state == RUDP_STATE_CLOSED)
		{
			out = &rudp->peers[i];
			SDL_LockMutex(out->mutex);
			out->targeted = target;
			out->instigator = 0;
			out->last_recv = SDL_GetTicks();
			out->seq_no = rudp->initial_seq_no;
			out->window = (t_rudp_window){.queue = NULL, .received_data = NULL,
				.assembled_data = {.size = 0, .data = NULL, .cursor = 0}};
			return (out);
		}
	return (NULL);
}
