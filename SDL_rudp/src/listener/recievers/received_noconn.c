#include <rudp.h>

void	received_noconn(t_rudp *rudp, t_rudp_peer *peer)
{
	if (peer != NULL)
		peer_switch_state(rudp, peer, RUDP_STATE_CLOSED);
}
