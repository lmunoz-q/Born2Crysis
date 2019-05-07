#include <rudp.h>

/*
** test if the first block of data is exactly target_ack + 1 and complete
** if so, update target_ack, remove block from received_data, transform it, if
** size is < block size, add block to assembled data for multiple readings
** return the size read (0 if nothing done), return a negative value on error
*/

int		rudp_receive(t_rudp *rudp, int id, void *data, int size)
{
	t_rudp_peer		*peer;
	t_received_data	*tmp;
	void			*tmp_free;
	Uint32			start;
	Uint32			cuts;

	peer = &rudp->peers[id];
	SDL_LockMutex(peer->mutex);
	if (peer->state != RUDP_STATE_ACTIVE)
	{
		SDL_UnlockMutex(peer->mutex);
		return (-1);
	}
	if (peer->window.assembled_data.data != NULL)
	{
		if ((size_t)size >= peer->window.assembled_data.size - peer->window.assembled_data.cursor)
		{
			size = (int)(peer->window.assembled_data.size - peer->window.assembled_data.cursor);
			SDL_memcpy(data, &peer->window.assembled_data.data[peer->window.assembled_data.cursor], (size_t)size);
			SDL_free(peer->window.assembled_data.data);
			peer->window.assembled_data.data = NULL;
			peer->window.assembled_data.cursor = 0;
			peer->window.assembled_data.size = 0;
			SDL_UnlockMutex(peer->mutex);
			return (size);
		}
		else
		{
			SDL_memcpy(data, &peer->window.assembled_data.data[peer->window.assembled_data.cursor], (size_t)size);
			peer->window.assembled_data.cursor += size;
			SDL_UnlockMutex(peer->mutex);
			return (size);
		}
	}
	if (peer->window.received_data == NULL || peer->window.received_data->seq_start != peer->target_seq_no)
	{
		SDL_UnlockMutex(peer->mutex);
		return (0);
	}
	peer->window.assembled_data.size = 0;
	tmp = peer->window.received_data;
	start = tmp->seq_start;
	cuts = 0;
	while (tmp != NULL && tmp->seq_start == start)
	{
		++cuts;
		peer->window.assembled_data.size += tmp->size;
		tmp = tmp->next;
	}
	if (cuts == peer->window.received_data->seq_len)
	{
		tmp = peer->window.received_data;
		peer->target_seq_no = tmp->seq_start + tmp->seq_len;
		peer->window.assembled_data.cursor = 0;
		if (peer->window.assembled_data.size <= (size_t)size)
			peer->window.assembled_data.data = data;
		else if ((peer->window.assembled_data.data = SDL_malloc(peer->window.assembled_data.size)) == NULL)
		{
			SDL_UnlockMutex(peer->mutex);
			return (-1);
		}
		while (cuts-- && tmp->seq_start == start)
		{
			SDL_memcpy(&peer->window.assembled_data.data[peer->window.assembled_data.cursor], tmp->data, tmp->size);
			peer->window.assembled_data.cursor += tmp->size;
			tmp_free = tmp;
			tmp = tmp->next;
			if (tmp != NULL)
				tmp->prev = NULL;
			SDL_free(tmp_free);
		}
		peer->window.received_data = tmp;
		if (size > (int)peer->window.assembled_data.cursor)
			size = (int)peer->window.assembled_data.cursor;
		if (peer->window.assembled_data.data == data)
			peer->window.assembled_data.data = NULL;
		else
		{
			SDL_memcpy(data, peer->window.assembled_data.data, (size_t)size);
			peer->window.assembled_data.cursor = (size_t)size;
		}
		SDL_UnlockMutex(peer->mutex);
		return (size);
	}
	SDL_UnlockMutex(peer->mutex);
	return (0);
}
