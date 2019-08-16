#include <asm.h>

int				init_process(t_process *p, t_data param[3], uint8_t *code,
	size_t code_size)
{
	if (code_size >= MAXIMUM_CODE_SIZE)
		return (-1);
	*p = (t_process){
		.registers = {
			[ARI_STACK_PTR] = {.u = (uint64_t)p->stack},
			[ARI_STACK_SIZE] = {.u = MAXIMUM_STACK_SIZE},
			[ARI_PARAM_0] = {.ptr = &param[0]},
			[ARI_PARAM_1] = {.ptr = &param[1]},
			[ARI_PARAM_2] = {.ptr = &param[2]}
		},
		.code_size = code_size,
		.state = PS_PAUSE
	};
	SDL_memcpy(p->code, code, code_size);
	return (0);
}
