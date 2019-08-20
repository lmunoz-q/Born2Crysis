#include <asm.h>

/*
** will take all the args designed in targets and make sure that they are of
** similar type, promotion order:
** AT_UNSIGNED -> AT_SIGNED -> AT_FLOAT
*/

/*
int	same_type_args(t_process *p, const int targets[], const int nb_targets)
{
	int		i;
	uint8_t	mask;
	uint8_t	tmp;

	mask = 0;
	i = -1;
	while (++i < nb_targets)
		mask |= p->op_args[targets[i]].type;
	i = -1;
	if (mask & AT_FLOAT)
		while (++i < nb_targets)
			if (!((tmp = p->op_args[targets[i]].type) & AT_FLOAT))
				p->op_args[targets[i]] = (t_typed_data){.type = AT_FLOAT,
					.data = {.f = tmp & AT_SIGNED ? p->op_args[targets[i]].data->}}
}
*/
