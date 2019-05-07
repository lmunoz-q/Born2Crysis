#include <rudp.h>

const char	*stringify_rudp_state(enum e_state state)
{
	// static const char	*unknown = "unknown state";
	static const char	*msg[] = {"init", "active", "closing", "closed"};

	return (msg[state]);
}
