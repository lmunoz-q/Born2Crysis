#include <asm.h>

int	op_andl(t_process *p)
{
	p->op_args[0].type = AT_UNSIGNED;
	p->op_args[0].data->u = p->op_args[1].data->u && p->op_args[2].data->u;
	test_zero(p, p->op_args[0].data->u);
	return (0);
}
