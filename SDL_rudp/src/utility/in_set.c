#include <rudp.h>

int		in_set(int v, size_t l, int s[])
{
	size_t	i;

	i = (size_t)-1;
	while (++i < l)
		if (v == s[i])
			return (1);
	return (0);
}
