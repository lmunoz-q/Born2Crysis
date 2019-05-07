#include <rudp.h>

/*
** switch to disconnecting, send the disconnect packet until ack, then switch to closed
** the disconnect packet behave similarly to the no connection packet, except it also triggers a response (ack)
*/

int		rudp_disconnect(t_rudp *rudp, int id)
{
	t_rudp_peer	*peer;
	Uint32		tick;

	if (rudp == NULL)
		return (RUDP_ERROR_NULL_POINTER);
	if (id < 0 || id > (int)rudp->nb_connections)
		return (RUDP_ERROR_INVALID_ID);
	peer = &rudp->peers[id];
	SDL_LockMutex(peer->mutex);
	if (peer->state != RUDP_STATE_ACTIVE)
	{
		SDL_UnlockMutex(peer->mutex);
		return (RUDP_ERROR_CLOSED_CONNECTION);
	}
	queue_fin_msg(rudp, peer);
	peer_switch_state(rudp, peer, RUDP_STATE_CLOSING);
	tick = SDL_GetTicks();
	SDL_UnlockMutex(peer->mutex);
	while (peer->state == RUDP_STATE_CLOSING
			&& SDL_GetTicks() < tick + RUDP_SYN_TIMEOUT)
		;
	return (0);
}
