/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_float64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:00 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:01 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** will try to extract an int64 from the parameter
** from a symbol will read the memory as int64
*/

t_error_type	get_float64(t_processor *p, t_op_param *param, double *flt)
{
	if (param->location == PL_IMMEDIATE)
	{
		if (param->type != OPT_FLOAT)
			return (p->error = ET_INVALID_PARAMETER_TYPE);
		*flt = param->data.f;
	}
	else if (param->location == PL_ALIAS)
	{
		if (param->data.index >= p->func->alias_size)
			return (p->error = ET_INVALID_PARAMETER);
		if (p->func->alias_memory[param->data.index].type != PT_F64)
			return (p->error = ET_INVALID_PARAMETER_TYPE);
		*flt = *p->func->alias_memory[param->data.index].data.f64;
	}
	else if (param->location == PL_SYMBOL)
	{
		if (param->data.index >= p->func->needed_symbols)
			return (p->error = ET_INVALID_PARAMETER);
		if (p->func->symbols[param->data.index].type != ST_POINTER)
			return (p->error = ET_INVALID_SYMBOL_TYPE);
		*flt = *(double *)p->func->symbols[param->data.index].ptr;
	}
	else
		return (p->error = ET_INVALID_PARAMETER_LOCATION);
	return (ET_OK);
}
