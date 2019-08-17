#include <asm.h>

t_process	*create_process(t_asmc *asmc, size_t entry_point, t_data param[3])
{
	t_process	*out;

	if (asmc == NULL)
		return (NULL);
	if ((out = SDL_malloc(sizeof(t_process)
			+ sizeof(t_data) * asmc->initial_stack_size)) == NULL)
		return (NULL);
	*out = (t_process){
		.registers = {
			[ARI_STACK_PTR] = {.ptr = out->stack},
			[ARI_STACK_SIZE] = {.u = asmc->initial_stack_size},
			[ARI_PARAM_0] = {.ptr = param == NULL ? NULL : &param[0]},
			[ARI_PARAM_1] = {.ptr = param == NULL ? NULL : &param[1]},
			[ARI_PARAM_2] = {.ptr = param == NULL ? NULL : &param[2]},
			[ARI_INST_PTR] = {.u = entry_point}},
		.state = PS_PAUSE,
		.asmc = asmc};
	SDL_memset(out->stack, 0, sizeof(t_data) * asmc->initial_stack_size);
	return (out);
}
