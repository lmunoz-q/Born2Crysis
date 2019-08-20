#include <asm.h>

int	op_add(t_process *p)
{
	if ((p->op_args[1].type & AT_MASK) != (p->op_args[2].type & AT_MASK))
		return (-1);
	p->op_args[0].type = p->op_args[1].type & AT_MASK;
	if (p->op_args[0].type == AT_FLOAT)
		p->op_args[0].data->f = p->op_args[1].data->f + p->op_args[2].data->f;
	else
		p->op_args[0].data->u = p->op_args[1].data->u + p->op_args[2].data->u;
	test_zero(p, p->op_args[0].data->u);
	return (0);
}
