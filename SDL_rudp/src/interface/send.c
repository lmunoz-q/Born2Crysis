#include <rudp.h>

int		valid_param(t_rudp *rudp, int id, void *data/*, Uint64 size*/)
{
	// if (size <= 0)
	// 	return (RUDP_ERROR_INVALID_SIZE);
	if (rudp == NULL || data == NULL)
		return (RUDP_ERROR_NULL_POINTER);
	if (id < 0 || id > (int)rudp->nb_connections)
		return (RUDP_ERROR_INVALID_ID);
	if (rudp->peers[id].state != RUDP_STATE_ACTIVE)
		return (RUDP_ERROR_CLOSED_CONNECTION);
	return (0);
}

int		acknowledge_data(t_rudp *rudp, t_rudp_peer *peer, t_packet_out *pack, void *data)
{
	(void)rudp;
	(void)data;
	(void)peer;
	(void)pack;
	return (0);
}

int		rudp_send(t_rudp *rudp, int id, void *data, Uint64 size)
{
	UDPpacket		*pack;
	t_queue_mode	mode;
	Uint32			len;
	Uint32			cut;
	Uint16			psize;

	if ((cut = (Uint32)valid_param(rudp, id, data/*, size*/)))
		return (cut);
	len = (Uint32)(size / RUDP_MAXIMUM_DATA_SIZE);
	len += size > len * RUDP_MAXIMUM_DATA_SIZE;
	cut = (Uint32)-1;
	SDL_LockMutex(rudp->peers[id].mutex);
	if (rudp->peers[id].state != RUDP_STATE_ACTIVE)
	{
		SDL_UnlockMutex(rudp->peers[id].mutex);
		return (-1);
	}
	mode = (t_queue_mode){.delay = 0, .need_ack = 1, .can_timeout = 0,
		.on_ack = acknowledge_data};
	while (++cut < len)
	{
		if (cut == len - 1)
			psize = (Uint16)(size - cut * RUDP_MAXIMUM_DATA_SIZE);
		else
			psize = RUDP_MAXIMUM_DATA_SIZE;
		pack = SDL_malloc(sizeof(UDPpacket) + psize + RUDP_OFFSET_DATA);
		if (pack == NULL)
			return (-1);
		*pack = (UDPpacket){.data = &((Uint8*)pack)[sizeof(UDPpacket)],
			.maxlen = psize + RUDP_OFFSET_DATA, .len = psize + RUDP_OFFSET_DATA,
	.address = {.host = rudp->peers[id].targeted.host, .port = rudp->port_out}};
		mode.on_ack_data = pack;
		mode.ack = ++rudp->peers[id].seq_no;
		pack->data[RUDP_OFFSET_TYPE] = RUDP_TYPE_DATA;
		write_32(&pack->data[RUDP_OFFSET_ACK], mode.ack);
		write_32(&pack->data[RUDP_OFFSET_CUT], cut);
		write_32(&pack->data[RUDP_OFFSET_LEN], len);
		write_16(&pack->data[RUDP_OFFSET_SIZE], psize);
		SDL_memcpy(&pack->data[RUDP_OFFSET_DATA], data, (size_t)psize);
		if (queue_packet(rudp, &rudp->peers[id], pack, mode) == NULL)
		{
			SDL_UnlockMutex(rudp->peers[id].mutex);
			return (-1);
		}
		data += RUDP_MAXIMUM_DATA_SIZE;
	}
	SDL_UnlockMutex(rudp->peers[id].mutex);
	return (0);
}
