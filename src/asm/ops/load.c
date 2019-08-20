#include <asm.h>

/*
** loads all common, param, stack and inst_ptr registers from the stack
** return and flags aren't modified (return being the expected way of
** communicating between functions and calls)
*/

/*
** a function call is similar to a snap + jump (but not equal, the inst_ptr in
** the snap will be different)
*/

int	op_load(t_process *p)
{
	if (p->registers[ARI_STACK_HEAD].u - ARI_RETURN
			>= p->registers[ARI_STACK_SIZE].u)
		return (-1);
	SDL_memcpy(p->registers, &((t_data*)p->registers[ARI_STACK_PTR].ptr)[
		p->registers[ARI_STACK_HEAD].u - ARI_RETURN],
		sizeof(t_data) * ARI_RETURN);
	return (0);
}
