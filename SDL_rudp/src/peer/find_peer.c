#include <rudp.h>

t_rudp_peer	*find_peer(t_rudp *rudp, IPaddress target)
{
	Uint32	i;

	i = (Uint32)-1;
	while (++i < rudp->nb_connections)
		if (rudp->peers[i].targeted.host == target.host
				/*&& rudp->peers[i].targeted.port == target.port*/ //temporary disabled
				&& rudp->peers[i].state != RUDP_STATE_CLOSED)
		{
			SDL_LockMutex(rudp->peers[i].mutex);
			return (&rudp->peers[i]);
		}
	return (NULL);
}
