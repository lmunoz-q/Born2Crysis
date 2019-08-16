#include <asm.h>

int	op_cmp(t_process *p)
{
	if (p->op_args[0].data->u != p->op_args[1].data->u)
		p->registers[ARI_FLAGS].u &= ~RF_ZERO;
	else
		p->registers[ARI_FLAGS].u |= RF_ZERO;
	return (0);
}
