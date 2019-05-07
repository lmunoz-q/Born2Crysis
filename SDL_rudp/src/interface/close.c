#include <rudp.h>

int		rudp_close(t_rudp *rudp)
{
	rudp->running = 0;
	SDL_WaitThread(rudp->listener_thread, NULL);
	SDL_WaitThread(rudp->sender_thread, NULL);
	//free all the stuff
	return (0);
}
