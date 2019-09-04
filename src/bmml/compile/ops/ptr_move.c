/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:38:57 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:38:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** restriction:
** param 0 must be modifiable (alias/symbol)
** param 1 must be integer
*/

t_error_type	compile_ptr_move(int ins, t_compiler *comp)
{
	t_op_param	*params;

	params = eval_params(comp, 2);
	if (comp->error.type != ET_OK)
		return (comp->error.type);
	if (params[0].location == PL_IMMEDIATE || params[1].type != OPT_INTEGER)
	{
		set_error(comp, ET_INVALID_PARAMETER);
		return (ET_INVALID_PARAMETER);
	}
	write_op(comp, ins, params, 2);
	return (comp->error.type);
}
