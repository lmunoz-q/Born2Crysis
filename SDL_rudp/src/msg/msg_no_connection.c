#include <rudp.h>

int		msg_no_connection(t_rudp *rudp, Uint32 target)
{
	UDPpacket	*pack;

	if ((pack = SDL_malloc(sizeof(UDPpacket) + 1)) == NULL)
		return (0);
	*pack = (UDPpacket){.data = &((Uint8*)pack)[sizeof(UDPpacket)], .len = 1,
		.maxlen = 1, .address = {.port = rudp->port_out, .host = target}};
	pack->data[0] = RUDP_TYPE_NOCONN;
	return (SDLNet_UDP_Send(rudp->sender_socket, -1, pack));
}
