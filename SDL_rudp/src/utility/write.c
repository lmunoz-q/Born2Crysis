#include <rudp.h>

void	write_16(Uint8 *data, Uint16 v)
{
	data[0] = (Uint8)(v >> 8);
	data[1] = (Uint8)v;
}

void	write_32(Uint8 *data, Uint32 v)
{
	data[0] = (Uint8)(v >> 24);
	data[1] = (Uint8)(v >> 16);
	data[2] = (Uint8)(v >> 8);
	data[3] = (Uint8)v;
}

void	write_64(Uint8 *data, Uint64 v)
{
	data[0] = (Uint8)(v >> 56);
	data[1] = (Uint8)(v >> 48);
	data[2] = (Uint8)(v >> 40);
	data[3] = (Uint8)(v >> 32);
	data[4] = (Uint8)(v >> 24);
	data[5] = (Uint8)(v >> 16);
	data[6] = (Uint8)(v >> 8);
	data[7] = (Uint8)v;
}
