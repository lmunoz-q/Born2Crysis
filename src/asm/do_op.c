#include <asm.h>

//load, decode and exectue a single operation
int	do_op(t_process *p)
{
	uint8_t	op;

	if (p->registers[ARI_INST_PTR].u >= p->asmc->code_size)
		return (1);
	op = p->asmc->code[p->registers[ARI_INST_PTR].u++];
	if (g_op_table[op].func == NULL)
		return (0);
	if (op > AOI_XOR)
		return (-1);
	SDL_memset(p->op_args, 0, sizeof(p->op_args));
	if (process_load_op_args(p, g_op_table[op].nb_args))
		return (-1);
	return (g_op_table[op].func(p));
}
