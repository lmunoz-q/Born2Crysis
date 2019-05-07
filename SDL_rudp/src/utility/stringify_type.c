#include <rudp.h>

const char	*stringify_type(enum e_type type)
{
	// static const char	*unknown = "unknown type";
	static const char	*msg[] = {"null", "free", "syn", "ack", "data", "fin",
								   "noconn"};

	return (msg[type]);
}
