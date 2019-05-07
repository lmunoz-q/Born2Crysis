#include <rudp.h>

int	rudp_attach_connection_attempt_receiver(t_rudp *rudp,
							t_connection_attempt_callback cb, void *user_data)
{
	if (rudp == NULL)
		return (RUDP_ERROR_NULL_POINTER);
	rudp->connection_attempt_callback = cb;
	rudp->connection_attempt_user_data = user_data;
	return (RUDP_ERROR_OK);
}
