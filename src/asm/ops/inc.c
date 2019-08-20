#include <asm.h>

int	op_inc(t_process *p)
{
	if ((p->op_args[0].type & AT_MASK) == AT_FLOAT)
		if (!++p->op_args[0].data->f)
			p->registers[ARI_FLAGS].u |= RF_ZERO;
	if ((p->op_args[0].type & AT_MASK) == AT_SIGNED)
	{
		if (!++p->op_args[0].data->i)
			p->registers[ARI_FLAGS].u |= RF_ZERO;
	}
	if ((p->op_args[0].type & AT_MASK) == AT_UNSIGNED)
		if (!++p->op_args[0].data->i)
			p->registers[ARI_FLAGS].u |= RF_ZERO;
	return (0);
}
