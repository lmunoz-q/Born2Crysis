#include <rudp.h>

void	peer_destroy_window(t_rudp *rudp, t_rudp_window *win)
{
	struct s_received_data	*it1;
	t_packet_out			*it2;
	struct s_received_data	*tmp1;
	t_packet_out			*tmp2;
	int						c;

	it1 = win->received_data;
	while (it1 != NULL)
	{
		tmp1 = it1;
		it1 = it1->next;
		tmp1->next = NULL;
		SDL_free(tmp1);
	}
	it2 = win->queue;
	c = 0;
	while (it2 != NULL)
	{
		tmp2 = it2;
		++c;
		it2 = it2->next;
		SDL_free(tmp2->packet);
		tmp2->packet = NULL;
		tmp2->prev = NULL;
		tmp2->next = NULL;
		SDL_free(tmp2);
	}
	printf("%s: packet lost/not sent: %d\n", rudp->name, c);
}

int		peer_switch_state(t_rudp *rudp, t_rudp_peer *peer, Uint32 state)
{
	static int		(*state_functions[4])(t_rudp*, UDPpacket*, t_rudp_peer*) = {
		[RUDP_STATE_INIT] = listener_init_state,
		[RUDP_STATE_ACTIVE] = listener_active_state,
		[RUDP_STATE_CLOSING] = listener_closing_state,
		[RUDP_STATE_CLOSED] = listener_closed_state};

	if (state == RUDP_STATE_CLOSED && peer->state != RUDP_STATE_CLOSED)
	{
		--rudp->used_connections;
		peer->last_recv = 0;
		peer->instigator = 0;
		peer_destroy_window(rudp, &peer->window);
		peer->window = (t_rudp_window){.received_data = NULL, .queue = NULL, .assembled_data = {.size = 0, .data = NULL, .cursor = 0}};
	}
	if (state == RUDP_STATE_INIT && peer->state == RUDP_STATE_CLOSED)
		++rudp->used_connections;
	peer->state_function = state_functions[state];
	peer->state = state;
	return (0);
}
