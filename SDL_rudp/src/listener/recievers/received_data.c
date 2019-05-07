#include <rudp.h>

/*
** insert in order in received_data if not already treated (target_seq_no >= ack or ack already present in list)
*/

int		received_data(t_rudp *rudp, t_rudp_peer *peer, UDPpacket *pack)
{
	t_received_data	*tmp;
	t_received_data	*out;
	Uint32			ack;
	Uint16			psize;

	(void)rudp;
	ack = read_32(&pack->data[RUDP_OFFSET_ACK]);
	if (ack < peer->target_seq_no)
		return (0);
	if ((tmp = peer->window.received_data) != NULL)
	{
		if (tmp->seq_no > ack)
			tmp = NULL;
		else if (tmp->seq_no <= ack)
		{
			while (tmp->next != NULL && tmp->next->seq_no <= ack)
				tmp = tmp->next;
			if (tmp->seq_no == ack)
				return (0);
		}
	}
	psize = read_16(&pack->data[RUDP_OFFSET_SIZE]);
	if ((out = SDL_malloc(sizeof(t_received_data) + psize)) == NULL)
		return (-1);
	*out = (t_received_data){.seq_no = ack, .prev = tmp, .size = psize,
		.seq_len = read_32(&pack->data[RUDP_OFFSET_LEN]),
		.seq_start = ack - read_32(&pack->data[RUDP_OFFSET_CUT])};
	SDL_memcpy(out->data, &pack->data[RUDP_OFFSET_DATA], out->size);
	if (tmp != NULL)
	{
		out->next = tmp->next;
		tmp->next = out;
		if (out->next != NULL)
			out->next->prev = out;
	}
	else
	{
		out->next = peer->window.received_data;
		peer->window.received_data = out;
	}
	return (0);
}
