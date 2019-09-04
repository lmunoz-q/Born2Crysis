/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:38:54 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:38:56 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** restriction:
** param 0 must be modifiable (alias/symbol)
*/

t_error_type	compile_common_3(int ins, t_compiler *comp)
{
	t_op_param	*params;

	params = eval_params(comp, 3);
	if (comp->error.type != ET_OK)
		return (comp->error.type);
	if (params[0].location == PL_IMMEDIATE)
	{
		set_error(comp, ET_INVALID_PARAMETER);
		return (ET_INVALID_PARAMETER);
	}
	write_op(comp, ins, params, 3);
	return (comp->error.type);
}
