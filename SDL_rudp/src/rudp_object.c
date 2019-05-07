#include <rudp.h>

t_rudp	*rudp_fail(t_rudp *out)
{
	Uint32	i;

	if (out->listener_socket != NULL)
		SDLNet_UDP_Close(out->listener_socket);
	if (out->sender_socket != NULL)
		SDLNet_UDP_Close(out->sender_socket);
	i = (Uint32)-1;
	while (++i < out->nb_connections)
		if (out->peers[i].mutex != NULL)
			SDL_DestroyMutex(out->peers[i].mutex);
	SDL_free(out->peers);
	SDL_free(out);
	return (NULL);
}

int		init_peers(t_rudp *out)
{
	Uint32	i;

	i = (Uint32)-1;
	while (++i < out->nb_connections)
	{
		out->peers[i] = (t_rudp_peer){
			.window = {.received_data = NULL, .queue = NULL,
				.assembled_data = {.data = NULL}},
			.state = RUDP_STATE_CLOSED, .last_recv = 0, .instigator = 0,
			.seq_no = 0, .mutex = SDL_CreateMutex(),
			.state_function = listener_closed_state, .targeted = {}};
		if (out->peers[i].mutex == NULL)
			return (-1);
	}
	return (0);
}

/*
** port_in: listener_port of this rudp object
** port_out: listener_port of peer/client/server rudp object
** the port of the sender socket is always random and used as part of the
** identification of the peer/client/server in pair with the address
** if port_in == port_out -> peer connection
** if port_in != port_out -> server/client connection, opposite connection must
** have reversed port_in/port_out pair to be able to communicate
** if port_in == 0 || port_out == 0 -> invalid connection
*/

t_rudp	*rudp(Uint16 port_in, Uint16 port_out,
			Uint32 maximum_number_of_connections)
{
	t_rudp	*out;

	if (maximum_number_of_connections < 1 || maximum_number_of_connections > 64)
		return (NULL);
	if ((out = (t_rudp*)SDL_malloc(sizeof(t_rudp))) == NULL)
		return (NULL);
	out->nb_connections = maximum_number_of_connections;
	if ((out->peers = (t_rudp_peer*)SDL_malloc(sizeof(t_rudp_peer)
									* maximum_number_of_connections)) == NULL)
	{
		SDL_free(out);
		return (NULL);
	}
	if (init_peers(out))
		return (rudp_fail(out));
	out->initial_seq_no = 0;
	out->port_in = port_in;
	out->port_out = port_out;
	if ((out->listener_socket = SDLNet_UDP_Open(port_in)) == NULL)
		return (rudp_fail(out));
	if ((out->sender_socket = SDLNet_UDP_Open(0)) == NULL)
		return (rudp_fail(out));
	out->used_connections = 0;
	return (out);
}

/*
** start rudp threads
*/

int		start_rudp(t_rudp *rudp)
{
	(void)rudp;
	return (0);
}

/*
** close and free rudp
*/

void	stop_rudp(t_rudp *rudp)
{
	(void)rudp;
}
