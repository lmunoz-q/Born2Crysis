#include <rudp.h>

/*
** send a non ack rudp packet, the size is limited
*/

int	rudp_send_free(t_rudp *rudp, IPaddress target, int size, void *data)
{
	UDPpacket	*pack_out;

	if (rudp == NULL || (size > 0 && data == NULL))
		return (RUDP_ERROR_NULL_POINTER);
	if (size > RUDP_MAXIMUM_DATA_SIZE || size < 0)
		return (RUDP_ERROR_INVALID_SIZE);
	if ((pack_out = SDLNet_AllocPacket(size + 1)) == NULL)
		return (RUDP_ERROR_NO_MEMORY);
	pack_out->len = size + 1;
	pack_out->address = target;
	pack_out->data[0] = RUDP_TYPE_FREE;
	SDL_memcpy(&pack_out->data[1], data, (size_t)size);
	if (!SDLNet_UDP_Send(rudp->sender_socket, -1, pack_out))
	{
		SDLNet_FreePacket(pack_out);
		return (RUDP_ERROR_SDLNET);
	}
	SDLNet_FreePacket(pack_out);
	return (RUDP_ERROR_OK);
}
