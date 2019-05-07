#include <rudp.h>

t_rudp	*rudp_init(char *name, Uint16 port_in, Uint16 port_out,
					Uint32 maximum_number_of_connections)
{
	t_rudp	*out;
	char	thread_name[64];

	out = rudp(port_in, port_out, maximum_number_of_connections);
	if (out == NULL)
		return (NULL);
	out->name = name;
	out->running = 1;
	snprintf(thread_name, 63, "rudp_listener_thread (%s)", name);
	out->listener_thread = SDL_CreateThread((SDL_ThreadFunction)listener_thread,
											thread_name, out);
	snprintf(thread_name, 63, "rudp_sender_thread (%s)", name);
	out->sender_thread = SDL_CreateThread((SDL_ThreadFunction)sender_thread,
											thread_name, out);
	return (out);
}
