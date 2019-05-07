#include <rudp.h>

const char	*stringify_rudp_error(enum e_rudp_error err_code)
{
	static const char	*unknown = "unknown error";
	static const char	*msg[] = {"ok", "null pointer", "invalid ID",
		"closed connection", "no memory", "SDLNet", "invalid size",
		"max connections", "connection refused"};

	return (!err_code || err_code > (enum e_rudp_error)-9
			? msg[-err_code] : unknown);
}
