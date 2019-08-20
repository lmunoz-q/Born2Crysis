#include <asm.h>

int	asmc_add_code(t_asmc *asmc, t_asm_file *file)
{
	t_word	it;
	t_word	lid;

	if (asmc == NULL || file == NULL
			|| asmc->code_size + file->code_size >= MAXIMUM_CODE_SIZE)
		return (-1);
	it = -1;
	while (++it < file->nb_labels)
	{
		lid = -1;
		while (++lid < asmc->nb_labels)
			if (!SDL_strcmp(asmc->labels[lid], file->labels[it]))
			{
				if (file->label_type[it] == LT_LOCAL) //duplicate label
					return (-2);
				break;
			}
		if (lid == asmc->nb_labels) //new label
		{
			if (file->label_type[it] == LT_C) //missing definition
				return (-3);
			if (lid >= MAXIMUM_LABEL_COUNT)
				return (-4); //too many labels
			asmc->label_type[lid] = file->label_type[it];
			SDL_strlcpy(asmc->labels[lid], file->labels[it], MAXIMUM_LABEL_LENGTH);
			asmc->label_address[lid] = &asmc->code[asmc->code_size + file->label_deltas[it]];
			++asmc->nb_labels;
		}
	}
	SDL_memcpy(&asmc->code[asmc->code_size], file->code, file->code_size);
	asmc->code_size += file->code_size;
	if (file->expected_stack_size > asmc->initial_stack_size)
		asmc->initial_stack_size = file->expected_stack_size;
	return (0);
}
