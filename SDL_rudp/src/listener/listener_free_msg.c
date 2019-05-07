#include <rudp.h>

/*
** those packets are stored in a separate queue and only kept for a short period
** of time
*/

void	listener_free_msg(t_rudp *rudp, UDPpacket *pack)
{
	if (rudp->received_free_packet_callback != NULL)
		rudp->received_free_packet_callback(rudp, pack, rudp->received_free_packet_user_data);
}
