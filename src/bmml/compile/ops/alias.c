/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:38:38 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:38:40 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** one of the only function allowed to expand the alias list
** param 0: must be pointer (modifiable, but will not be modified)
** param 1: must be integer (any location)
** param 2: must be type (any location)
** param 3: must be string (special handling of alias)
** mini hack: will call eval_params with incorect size of 3
*/

t_error_type	compile_alias(int ins, t_compiler *comp)
{
	t_op_param	*params;

	params = eval_params(comp, 3);
	if (comp->error.type != ET_TOO_MANY_PARAMETERS)
	{
		if (comp->error.type == ET_ALLOCATION_FAILED)
			return (ET_ALLOCATION_FAILED);
		return (comp->error.type = ET_TOO_FEW_PARAMETERS);
	}
	comp->error.type = ET_OK;
	if (params[0].location == PL_IMMEDIATE || params[1].type != OPT_INTEGER
		|| params[2].type != OPT_TYPE)
	{
		set_error(comp, ET_INVALID_PARAMETER);
		return (ET_INVALID_PARAMETER);
	}
	if ((params[3] = (t_op_param){.location = PL_ALIAS, .type = OPT_INTEGER,
		.data = {.index = new_alias(comp, comp->head)}}).data.index
		== (uint64_t) - 1)
		return (comp->error.type);
	write_op(comp, ins, params, 4);
	return (comp->error.type);
}
