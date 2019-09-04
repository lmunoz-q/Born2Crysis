/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:27 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:28 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_error_type	get_delta(t_processor *p, t_op_param *param, int64_t *delta)
{
	t_data	val;

	if (param->location == PL_IMMEDIATE)
	{
		if (param->type == OPT_INTEGER)
			*delta = param->data.i;
		else
			return (p->error = ET_INVALID_PARAMETER_TYPE);
	}
	else if (param->location == PL_SYMBOL)
	{
		if (get_casted_parameter(p, param, &val, PT_I64) != ET_OK)
			return (p->error);
		*delta = val.i64;
	}
	else
		return (p->error = ET_INVALID_PARAMETER_LOCATION);
	return (ET_OK);
}

t_error_type	process_delta(t_processor *p, t_op_param *param)
{
	int64_t		delta;

	if (get_delta(p, &param[1], &delta) != ET_OK)
		return (p->error);
	if (param[0].location != PL_ALIAS)
		return (p->error = ET_INVALID_PARAMETER_LOCATION);
	if (param[0].data.index >= p->func->alias_size)
		return (p->error = ET_INVALID_PARAMETER);
	p->func->alias_memory[param[0].data.index].data.i8 =
		&p->func->alias_memory[param[0].data.index].data.i8[delta];
	return (p->error);
}
