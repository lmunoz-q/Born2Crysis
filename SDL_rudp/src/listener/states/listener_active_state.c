#include <rudp.h>

/*
** ACK -> do the ack thing
** SYN -> ACK, ignored
** DATA -> ACK, stored
** NULL -> not ACK, reset timer
** FIN -> switch state to CLOSING, ACK
*/

int		listener_active_state(t_rudp *rudp, UDPpacket *pack, t_rudp_peer *peer)
{
	if (pack->data[0] == RUDP_TYPE_ACK)
		received_ack(rudp, peer, read_32(&pack->data[1]));
	else if (pack->data[0] == RUDP_TYPE_DATA)
	{
		peer->last_recv = SDL_GetTicks();
		msg_acknowledge(rudp, pack->address.host, read_32(&pack->data[1]));
		received_data(rudp, peer, pack);
	}
	else if (pack->data[0] == RUDP_TYPE_NULL)
		peer->last_recv = SDL_GetTicks();
	else if (pack->data[0] == RUDP_TYPE_FIN)
	{
		msg_acknowledge(rudp, pack->address.host, read_32(&pack->data[1]));
		peer_switch_state(rudp, peer, RUDP_STATE_CLOSED);
	}
	else if (pack->data[0] == RUDP_TYPE_SYN)
		msg_acknowledge(rudp, pack->address.host, read_32(&pack->data[1]));
	return (0);
}
