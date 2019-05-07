#include <rudp.h>

#define MSG_LEN 4037
static char test_msg[MSG_LEN] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque non volutpat odio. Sed non egestas erat. Ut nec scelerisque massa, ut porta diam. Phasellus leo lectus, vestibulum eu magna ut, tempus accumsan ex. Curabitur vehicula maximus dignissim. Proin quis commodo neque. Donec dolor ligula, commodo non commodo id, suscipit et tortor. Aliquam bibendum fermentum quam, ut consectetur dolor condimentum et. Donec mollis mi erat, faucibus viverra nisi varius nec. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Fusce et lacus eu leo pulvinar ultricies. Vivamus vulputate pretium rutrum. Donec vitae tincidunt orci, non bibendum turpis. Donec ac congue est. Etiam ut commodo urna.\n"
								"Aenean fringilla justo lorem, eget scelerisque ex elementum id. Nam placerat hendrerit mi ac lobortis. In ultrices neque placerat viverra dapibus. Nunc a laoreet felis. Curabitur volutpat quis nulla nec efficitur. Nunc bibendum mauris nibh, vel tristique purus ultrices eu. Mauris nec mauris nec quam dictum rutrum. Mauris eget purus metus. Phasellus blandit libero nulla, dignissim pellentesque diam porta vitae. Quisque sagittis consectetur lobortis. Aenean pellentesque massa in metus consectetur volutpat.\n"
								"Duis at mauris sed elit hendrerit bibendum. Proin lectus nisl, dictum non tempor non, fermentum facilisis lorem. Aliquam eget purus vulputate, tempor sapien at, posuere orci. Maecenas vestibulum sem maximus justo hendrerit, eget suscipit nunc blandit. Ut tristique, nunc vel vulputate suscipit, ante nulla tempor libero, id dapibus dui libero vitae tellus. Nunc vel nisl odio. Maecenas volutpat, dolor vitae pharetra facilisis, felis nisl porta nisl, vitae aliquet erat eros eu ipsum. Etiam sed tortor vel sem blandit elementum. Maecenas euismod aliquam leo, eu vulputate nibh suscipit vel. Aliquam tempus consequat leo, vel commodo mauris malesuada eget.\n"
								"Curabitur bibendum, ipsum egestas semper bibendum, augue lorem sodales tortor, non placerat purus est eget metus. Aenean egestas efficitur dui. Aenean sem elit, auctor ac sem ut, volutpat ultricies ligula. Curabitur non lectus ullamcorper metus tempus rhoncus. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Ut malesuada eu tellus et egestas. Pellentesque lobortis orci nulla, consectetur blandit justo convallis non. Nunc id ante nunc. Integer consectetur nibh lorem, eu consectetur massa pretium sed. Donec ornare ex massa, sed auctor metus egestas et. Phasellus id dapibus libero. Sed accumsan ante id ipsum malesuada, ut euismod tellus finibus. Mauris faucibus turpis a massa euismod, finibus rhoncus libero feugiat.\n"
								"Mauris nec augue ut est fringilla ornare. Praesent ultrices id sem eu viverra. Nunc vestibulum porttitor nisl, ut laoreet enim fringilla id. Vestibulum suscipit, urna at tristique pretium, sapien dolor varius neque, vel auctor risus ante vel odio. Pellentesque in egestas dui. Ut in efficitur elit. Morbi volutpat interdum tempus. Cras sit amet ante elit. Etiam eu placerat massa. Mauris ornare vulputate elit, non rutrum ligula varius id. Aliquam sagittis vestibulum eleifend.\n"
								"Curabitur sapien mi, tristique eget vestibulum ac, imperdiet ut enim. In at arcu volutpat, dapibus nibh et, pharetra tortor. In sit amet metus auctor, convallis eros et, tempor ipsum. Sed erat lacus, facilisis quis lectus egestas, gravida commodo quam. Donec mollis nibh sit amet nibh venenatis sagittis. Aenean fermentum nunc ut enim sagittis egestas. Vestibulum blandit, libero non rutrum tincidunt, dolor massa euismod ligula, ac ultricies velit eros quis risus. Maecenas vulputate orci mauris, et mattis magna cursus non. Curabitur eleifend quis nisl id consectetur. Nam porttitor consequat tincidunt. In fringilla placerat nibh, id vulputate quam dapibus eget. Sed mollis pulvinar diam, sit amet vestibulum sapien vestibulum quis. In tempor dignissim erat, a dictum erat ullamcorper sit amet.\n"
								"Donec ut porttitor metus. Sed id leo magna. Interdum et malesuada fames ac ante ipsum primis in faucibus.";

int	server(void *data)
{
	char	*running;
	t_rudp	*rudp_obj;
	Uint32	tick;
	int		cc;

	running = data;
	rudp_obj = rudp_init("server", 0x4444, 0x4242, 1);
	rudp_obj->initial_seq_no = 123456;
	tick = SDL_GetTicks();
	cc = 0;
	while (*running || rudp_obj->used_connections)
	{
		if (cc == 0 && rudp_obj->used_connections)
		{
			printf("client detected\n");
			cc = 1;
		}
		if (SDL_GetTicks() > tick + 16)
		{
			rudp_send(rudp_obj, 0, test_msg, MSG_LEN);
			tick = SDL_GetTicks();
		}
	}
	rudp_close(rudp_obj);
	return (0);
}

int	client(void *data)
{
	char	*running;
	char	*ip;
	t_rudp	*rudp_obj;
	int		id;
	char	received[MSG_LEN + 10];
	int		l;
	int		total;

	running = data;
	ip = &((char*)data)[1];
	rudp_obj = rudp_init("client", 0x4242, 0x4444, 1);
	rudp_obj->initial_seq_no = 654321;
	id = rudp_connect(rudp_obj, ip);
	if (id < 0)
		printf("fail to connect\n");
	total = 0;
	while (id >= 0 && *running)
		if ((l = rudp_receive(rudp_obj, id, received, MSG_LEN + 10)) > 0)
		{
			if (l != MSG_LEN || SDL_memcmp(test_msg, received, MSG_LEN))
				exit(0 * printf("DA FAILURE %d '%.*s'\n", l, l, received));
			total += l;
			printf("%dM %dK %d\n", total >> 20, (total >> 10) & 0x3FF, total & 0x3FF);
		}
	rudp_disconnect(rudp_obj, id);
	rudp_close(rudp_obj);
	return (0);
}

int	main(int argc, char *argv[])
{
	char		ip[17];
	char		local_ip[16];
	SDL_Thread	*t;

	if (argc < 2 || (SDL_strcmp(argv[1], "client") && SDL_strcmp(argv[1], "server")))
	{
		printf("%s [client <ip>] [server]\n", argv[0]);
		return (0);
	}
	SDL_Init(SDL_INIT_EVERYTHING);
	stringify_ip(get_my_local_ip(), local_ip);
	printf("local ip: %s\n", local_ip);
	ip[0] = 1;
	if (!SDL_strcmp(argv[1], "client"))
	{
		if (argc > 2)
		{
			SDL_memcpy(&ip[1], argv[2], SDL_strlen(argv[2]) < 15 ? SDL_strlen(argv[2]) + 1 : 15);
			ip[16] = '\0';
		}
		else
			SDL_memcpy(&ip[1], "127.0.0.1", 10);
		t = SDL_CreateThread(client, "client", ip);
		SDL_Delay(30000);
		ip[0] = 0;
		SDL_WaitThread(t, NULL);
	}
	else
	{
		t = SDL_CreateThread(server, "server", ip);
		SDL_Delay(30000);
		ip[0] = 0;
		SDL_WaitThread(t, NULL);
	}
	return (0);
}
