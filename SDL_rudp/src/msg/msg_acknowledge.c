#include <rudp.h>

int		msg_acknowledge(t_rudp *rudp, Uint32 target, Uint32 ack)
{
	UDPpacket	*pack;

	if ((pack = SDL_malloc(sizeof(UDPpacket) + 5)) == NULL)
		return (0);
	*pack = (UDPpacket){.data = &((Uint8*)pack)[sizeof(UDPpacket)], .len = 5,
		.maxlen = 5, .address = {.port = rudp->port_out, .host = target}};
	pack->data[0] = RUDP_TYPE_ACK;
	write_32(&pack->data[1], ack);
	return (SDLNet_UDP_Send(rudp->sender_socket, -1, pack));
}
