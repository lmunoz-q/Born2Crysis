/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:38:46 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:38:47 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** param 0: sym only
** param 1: must be modifiable
*/

t_error_type	compile_call(int ins, t_compiler *comp)
{
	t_op_param	*params;

	params = eval_params(comp, 2);
	if (comp->error.type != ET_OK)
		return (comp->error.type);
	if (params[0].location != PL_SYMBOL || params[1].location == PL_IMMEDIATE)
	{
		set_error(comp, ET_INVALID_PARAMETER);
		return (ET_INVALID_PARAMETER);
	}
	write_op(comp, ins, params, 2);
	return (comp->error.type);
}
