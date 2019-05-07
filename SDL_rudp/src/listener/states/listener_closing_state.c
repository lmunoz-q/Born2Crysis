#include <rudp.h>

/*
** ACK -> switch state to CLOSED (via ack callback)
** FIN -> ignored, ACK
** DATA, SYN -> ACK, NOCONN
** NULL -> ignored
*/

int		listener_closing_state(t_rudp *rudp, UDPpacket *pack, t_rudp_peer *peer)
{
	if (pack->data[0] == RUDP_TYPE_ACK)
		received_ack(rudp, peer, read_32(&pack->data[1]));
	else if (pack->data[0] == RUDP_TYPE_FIN)
		msg_acknowledge(rudp, pack->address.host, read_32(&pack->data[1]));
	else if (pack->data[0] == RUDP_TYPE_DATA || pack->data[0] == RUDP_TYPE_SYN)
		msg_no_connection(rudp, pack->address.host);
	return (0);
}
