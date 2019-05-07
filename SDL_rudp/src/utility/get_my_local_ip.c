#include <rudp.h>

static inline Uint32	i_gmli_finalize(UDPsocket s[2], UDPpacket *p[2],
										Uint32 ip)
{
	SDLNet_UDP_Close(s[0]);
	SDLNet_UDP_Close(s[1]);
	SDLNet_FreePacket(p[0]);
	SDLNet_FreePacket(p[1]);
	return (ip);
}

Uint32					get_my_local_ip(void)
{
	UDPsocket						out;
	UDPpacket						*out_packet;
	IPaddress						ip;
	UDPsocket						in;
	UDPpacket						*packet_in;

	out = SDLNet_UDP_Open(0);
	out_packet = SDLNet_AllocPacket(6);
	packet_in = SDLNet_AllocPacket(6);
	in = SDLNet_UDP_Open(0xFFFF);
	SDLNet_ResolveHost(&ip, "255.255.255.255", 0xFFFF);
	out_packet->address = ip;
	out_packet->len = 6;
	SDL_memcpy(out_packet->data, (Uint8*)"my_ip", 6);
	while (ip.port--)
	{
		SDLNet_UDP_Send(out, -1, out_packet);
		if (SDLNet_UDP_Recv(in, packet_in) && packet_in->len == 6
			&& !SDL_memcmp(packet_in->data, out_packet->data, 6))
			return (i_gmli_finalize((UDPsocket[2]){in, out},
									(UDPpacket*[2]){out_packet, packet_in},
									packet_in->address.host));
	}
	return (i_gmli_finalize((UDPsocket[2]){in, out},
						(UDPpacket*[2]){out_packet, packet_in}, 0xFFFFFFFF));
}
