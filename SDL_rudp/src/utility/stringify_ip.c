#include <rudp.h>

void	stringify_ip(Uint32 addr, char buff[15])
{
	sprintf(buff, "%hhu.%hhu.%hhu.%hhu", (Uint8)(addr),
			(Uint8)(addr >> 8), (Uint8)(addr >> 16), (Uint8)(addr >> 24));
}
