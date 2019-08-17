#include <asm.h>

inline void	test_zero(t_process *p, uint64_t v)
{
	if (v)
		p->registers[ARI_FLAGS].u &= ~RF_ZERO;
	else
		p->registers[ARI_FLAGS].u |= RF_ZERO;
}
