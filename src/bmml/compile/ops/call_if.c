/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_if.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:38:48 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:38:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** a la place du calif :p
** param 0: anything
** param 1: sym only
** param 2: must be modifiable
*/

t_error_type	compile_call_if(int ins, t_compiler *comp)
{
	t_op_param	*params;

	params = eval_params(comp, 3);
	if (comp->error.type != ET_OK)
		return (comp->error.type);
	if (params[1].location != PL_SYMBOL || params[2].location == PL_IMMEDIATE)
	{
		set_error(comp, ET_INVALID_PARAMETER);
		return (ET_INVALID_PARAMETER);
	}
	write_op(comp, ins, params, 3);
	return (comp->error.type);
}
