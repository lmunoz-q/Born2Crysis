#include <rudp.h>

int	rudp_attach_free_receiver(t_rudp *rudp, t_received_free_packet_callback cb,
								void *user_data)
{
	if (rudp == NULL)
		return (RUDP_ERROR_NULL_POINTER);
	rudp->received_free_packet_callback = cb;
	rudp->received_free_packet_user_data = user_data;
	return (RUDP_ERROR_OK);
}
