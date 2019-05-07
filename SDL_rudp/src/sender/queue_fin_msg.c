#include <rudp.h>

int	acknowledged_fin(t_rudp* rudp, t_rudp_peer *peer, t_packet_out *unused1,
						void *unused2)
{
	(void)unused1;
	(void)unused2;
	peer_switch_state(rudp, peer, RUDP_STATE_CLOSED);
	return (0);
}

int	timed_out_fin(t_rudp* rudp, t_rudp_peer *peer, t_packet_out *unused1,
					 void *unused2)
{
	(void)unused1;
	(void)unused2;
	peer_switch_state(rudp, peer, RUDP_STATE_CLOSED);
	return (0);
}

int	queue_fin_msg(t_rudp *rudp, t_rudp_peer *peer)
{
	UDPpacket	*pack;
	Uint32		ack;

	if ((pack = SDL_malloc(sizeof(UDPpacket) + 5)) == NULL)
		return (-1);
	ack = ++peer->seq_no;
	*pack = (UDPpacket){.data = &((Uint8*)pack)[sizeof(UDPpacket)], .len = 5,
		.maxlen = 5, .address = {
			.port = rudp->port_out, .host = peer->targeted.host}};
	pack->data[0] = RUDP_TYPE_FIN;
	write_32(&pack->data[1], ack);
	queue_packet(rudp, peer, pack, (t_queue_mode){.need_ack = 1,
		.can_timeout = 1, .ack = ack, .on_ack = acknowledged_fin,
		.on_ack_data = NULL, .timeout = RUDP_SYN_TIMEOUT,
		.on_timeout = timed_out_fin, .on_timeout_data = NULL, .delay = 0});
	return (rudp->errno);
}
