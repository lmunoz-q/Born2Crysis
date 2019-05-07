#include <rudp.h>

/*
** first: find a slot in rudp (if not return: RUDP_ERROR_MAX_CONNECTIONS)
** second: prepare the client, set it as INSTIGATOR (error: RUDP_ERROR_NO_MEMORY
** third: do a SYN ping pong with the target (error: RUDP_CONNECTION_REFUSED)
** return: connection ID or any of the error above
*/

/*
** C1 want to connect to C2 (double confirmation)
** C1S CLOSED: SYN out (until ACK/NOCONN/timeout), INIT state, INSTIGATOR
** C2L CLOSED: SYN in, NEW peer, INIT state, ACK out (once)
** C2S INIT: SYN out (until ACK/timeout)
** C1L INIT: ACK in, wait for SYN
** C1L INIT: SYN in (from targeted peer), ACTIVE state, ACK out (once)
** C2L INIT: ACK in, ACTIVE state
*/

/*
** create a connection to communicate to the distant device identified by the
** given ip, return a connection id (>=0) or negative value for error
*/

int	rudp_connect(t_rudp *rudp, const char ip[])
{
	IPaddress	ipa;
	int			id;
	t_rudp_peer	*peer;
	Uint32		tick;

	if (rudp == NULL || ip == NULL)
		return (RUDP_ERROR_NULL_POINTER);
	id = -1;
	while (++id < (int)rudp->nb_connections
			&& !SDL_LockMutex(rudp->peers[id].mutex)
			&& rudp->peers[id].state != RUDP_STATE_CLOSED)
		SDL_UnlockMutex(rudp->peers[id].mutex);
	if (id == (int)rudp->nb_connections)
		return (RUDP_ERROR_MAX_CONNECTIONS);
	SDLNet_ResolveHost(&ipa, ip, rudp->port_out);
	peer = &rudp->peers[id];
	peer->targeted = ipa;
	peer->seq_no = rudp->initial_seq_no;
	peer->instigator = 1;
	peer->hand_shook = 0;
	peer_switch_state(rudp, peer, RUDP_STATE_INIT);
	peer->last_recv = SDL_GetTicks();
	tick = peer->last_recv;
	queue_syn_msg(rudp, peer);
	SDL_UnlockMutex(rudp->peers[id].mutex);
	while (peer->state == RUDP_STATE_INIT && SDL_GetTicks() < tick + RUDP_SYN_TIMEOUT)
		;
	if (peer->state != RUDP_STATE_ACTIVE)
		return (RUDP_CONNECTION_REFUSED);
	return (id);
}
