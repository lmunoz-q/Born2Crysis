#include <rudp.h>

/*
** ACK -> switch state to ACTIVE (the switch is donne by the callback)
** SYN -> ACK, switch state to ACTIVE if INSTIGATOR
** DATA, FIN, NULL -> NOCONN
*/

int		listener_init_state(t_rudp *rudp, UDPpacket *pack, t_rudp_peer *peer)
{
	if (in_set(pack->data[0], 3, (int[3]){RUDP_TYPE_DATA, RUDP_TYPE_NULL,
			RUDP_TYPE_FIN}))
		msg_no_connection(rudp, pack->address.host);
	else if (pack->data[0] == RUDP_TYPE_NOCONN)
		peer_switch_state(rudp, peer, RUDP_STATE_CLOSED);
	else if (pack->data[0] == RUDP_TYPE_ACK)
		received_ack(rudp, peer, read_32(&pack->data[1]));
	else if (pack->data[0] == RUDP_TYPE_SYN)
	{
		peer->target_seq_no = read_32(&pack->data[RUDP_OFFSET_ACK]) + 1;
		msg_acknowledge(rudp, pack->address.host, read_32(&pack->data[RUDP_OFFSET_ACK]));
		if (peer->instigator && peer->hand_shook)
			peer_switch_state(rudp, peer, RUDP_STATE_ACTIVE);
	}
	return (0);
}
