#include <asm.h>

inline void	test_sign(t_process *p, t_typed_data d)
{
	if ((d.type & AT_UNSIGNED)
			|| (d.type & AT_SIGNED && d.data->i >= 0)
			|| (d.type & AT_FLOAT && d.data->f >= 0))
		p->registers[ARI_FLAGS].u &= ~RF_SIGN;
	else
		p->registers[ARI_FLAGS].u |= RF_SIGN;
}
