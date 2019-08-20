#include <asm.h>

int	asmc_add_exposed_function(t_asmc *asmc,
	const char label[MAXIMUM_LABEL_LENGTH - 2], int (*func)(t_process*))
{
	(void)asmc;
	(void)label;
	(void)func;
	return (0);
	/*
	t_word	it;
	char	clabel[MAXIMUM_LABEL_LENGTH];

	if (asmc == NULL)
		return (-1);
	clabel[0] = "C";
	clabel[1] = "_";
	SDL_strlcpy(&clabel[2], label, MAXIMUM_LABEL_LENGTH - 2);
	it = -1;
	while (++it < asmc->nb_labels)
		if (!SDL_strcmp(clabel, asmc->labels[it]))
		{
			if ()
		}
	*/
}
