#include <rudp.h>

/*
** C1 want to connect to C2 (double confirmation)
** C1S: SYN out (until ACK/NOCONN/timeout), INIT state, INSTIGATOR
** C2L: SYN in, NEW peer, INIT state, ACK out (once)
** C2S: SYN out (until ACK/timeout)
** C1L: ACK in, wait for SYN
** C1L: SYN in (from targeted peer), ACTIVE state, ACK out (once)
** C2L: ACK in, ACTIVE state
*/

/*
** SYN -> start INIT routine, not instigator, ACK, NOCONN if no place left,
**   SYN otherwise
** DATA, NULL, FIN -> NOCONN
** ACK -> ignored
*/

int		listener_closed_state(t_rudp *rudp, UDPpacket *pack, t_rudp_peer *peer)
{
	int	new;

	if (in_set(pack->data[0], 3, (int[3]){RUDP_TYPE_DATA, RUDP_TYPE_NULL,
			RUDP_TYPE_FIN}))
		msg_no_connection(rudp, pack->address.host);
	if (pack->data[0] == RUDP_TYPE_SYN)
	{
		msg_acknowledge(rudp, pack->address.host, read_32(&pack->data[1]));
		if (peer == NULL)
		{
			if (rudp->connection_attempt_callback != NULL && rudp->connection_attempt_callback(rudp, pack, rudp->connection_attempt_user_data)) //refused connection
			{
				msg_no_connection(rudp, pack->address.host);
				return (0);
			}
			new = 1;
			peer = new_peer(rudp, pack->address);
		}
		else
			new = 0;
		if (peer == NULL)
			return (!msg_no_connection(rudp, pack->address.host));
		peer->target_seq_no = read_32(&pack->data[1]) + 1;
		peer->instigator = 0;
		peer_switch_state(rudp, peer, RUDP_STATE_INIT);
		queue_syn_msg(rudp, peer);
		if (new)
			SDL_UnlockMutex(peer->mutex);
	}
	return (0);
}
