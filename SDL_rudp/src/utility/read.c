#include <rudp.h>

Uint16	read_16(const Uint8 *data)
{
	return ((((Uint16)data[0]) << 8) | (Uint16)data[1]);
}

Uint32	read_32(const Uint8 *data)
{
	return (((Uint32)data[0]) << 24 | (((Uint32)data[1]) << 16)
			| (((Uint32)data[2]) << 8) | (Uint32)data[3]);
}

Uint64	read_64(const Uint8 *data)
{
	return ((((Uint64)data[0]) << 56) | (((Uint64)data[1]) << 48)
			| (((Uint64)data[2]) << 40) | (((Uint64)data[3]) << 32)
			| (((Uint64)data[4]) << 24) | (((Uint64)data[5]) << 16)
			| (((Uint64)data[6]) << 8) | ((Uint64)data[7]));
}
