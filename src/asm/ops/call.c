#include <asm.h>

/*
** interface to call other asm or C exposed functions
** either reuse the current process for the call if the target is asm, or
** temporary pause the process while calling a C function
** any pointer outside the code of the asmc structure will be considered a
** pointer to a C function
*/

/*
** function interface:
*/

int	op_call(t_process *p)
{
	size_t	addr;
	t_data	ir;

	addr = p->op_args[1].data->u;
	if (addr >= (size_t)p->asmc->code
	&& addr < p->asmc->code_size + (size_t)p->asmc->code)
	{
		if (op_snap(p))
			return (-1);
		p->registers[ARI_INST_PTR].u = addr - (size_t)p->asmc->code;
		ir = p->registers[ARI_RETURN];
		p->registers[ARI_RETURN].ptr = p->op_args[0].data;
		SDL_memset(p->registers, 0, sizeof(t_data) * ARI_PARAM_0);
		p->registers[ARI_PARAM_0].ptr = p->op_args[2].data;
		p->registers[ARI_PARAM_1].ptr = p->op_args[3].data;
		p->registers[ARI_PARAM_2].ptr = p->op_args[4].data;
		run_process(p);
		p->registers[ARI_RETURN] = ir;
		op_load(p);
	}
	else
		if (((int (*)(t_process *p))addr)(p))
			return (-1);
	return (0);
}
