/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:38:43 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:38:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** one of the only function allowed to expand the alias list
** param 0: must be integer (any location)
** param 1: must be type (any location)
** param 2: must be string (special handling of alias)
** mini hack: will call eval_params with incorect size of 2
*/

t_error_type	compile_alloc(int ins, t_compiler *comp)
{
	t_op_param	*params;

	params = eval_params(comp, 2);
	if (comp->error.type != ET_TOO_MANY_PARAMETERS)
	{
		if (comp->error.type == ET_ALLOCATION_FAILED)
			return (ET_ALLOCATION_FAILED);
		return (comp->error.type = ET_TOO_FEW_PARAMETERS);
	}
	comp->error.type = ET_OK;
	if (params[0].type != OPT_INTEGER || params[1].type != OPT_TYPE)
	{
		set_error(comp, ET_INVALID_PARAMETER);
		return (ET_INVALID_PARAMETER);
	}
	if ((params[2] = (t_op_param){.location = PL_ALIAS, .type = OPT_INTEGER,
		.data = {.index = new_alias(comp, comp->head)}}).data.index
		== (uint64_t) - 1)
		return (comp->error.type);
	write_op(comp, ins, params, 3);
	return (comp->error.type);
}
