#include <rudp.h>

void	print_packet_info(int padding, UDPpacket *pack)
{
	Uint8	type;
	static const char padder[] = "                                             "
		"                                                                      "
		"                                                                      "
		"                                                                      "
		"                                                                     ";

	type = pack->data[RUDP_OFFSET_TYPE];
	printf("%.*stype: %s\n", padding, padder, stringify_type(type));
	if (!in_set(type, 3, (int[3]){RUDP_TYPE_NULL, RUDP_TYPE_FREE, RUDP_TYPE_NOCONN}))
		printf("%.*s  ack: %d\n", padding, padder, read_32(&pack->data[RUDP_OFFSET_ACK]));
	if (type == RUDP_TYPE_FREE)
		printf("%.*s  data: '%.80s'\n", padding, padder, &pack->data[RUDP_OFFSET_TYPE + 1]);
	if (type == RUDP_TYPE_DATA)
	{
		printf("%.*s  cut: %d\n", padding, padder, read_32(&pack->data[RUDP_OFFSET_CUT]));
		printf("%.*s  len: %d\n", padding, padder, read_32(&pack->data[RUDP_OFFSET_LEN]));
		printf("%.*s  size: %d\n", padding, padder, read_16(&pack->data[RUDP_OFFSET_SIZE]));
		printf("%.*s  data: '%.*s'\n", padding, padder, read_16(&pack->data[RUDP_OFFSET_SIZE]), &pack->data[RUDP_OFFSET_DATA]);
	}
}
