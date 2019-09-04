/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:04 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:05 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** this on return the actual type of the parameter
*/

t_error_type	get_param_type(t_processor *p, t_op_param *param,
								t_ptr_type *type)
{
	if (param->location == PL_IMMEDIATE)
	{
		if (param->type == OPT_INTEGER)
			*type = PT_I64;
		else if (param->type == OPT_FLOAT)
			*type = PT_F64;
		else
			return (p->error = ET_INVALID_PARAMETER_TYPE);
	}
	else if (param->location == PL_ALIAS)
	{
		if (param->data.index >= p->func->alias_size)
			return (p->error = ET_INVALID_PARAMETER);
		*type = p->func->alias_memory[param->data.index].type;
	}
	else if (param->location == PL_SYMBOL)
		*type = PT_I8;
	else
		return (p->error = ET_INVALID_PARAMETER_LOCATION);
	return (ET_OK);
}
