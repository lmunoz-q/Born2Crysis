/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:19 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:20 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** size (positive, non float) - type - name (sym location)
*/

t_error_type	process_alloc(t_processor *p, t_op_param *param)
{
	t_entry		*alias;
	t_ptr_type	type;
	t_data		val;

	if (get_param_type(p, &param[0], &type) != ET_OK)
		return (p->error);
	if (type == PT_F32 || type == PT_F64)
		return (p->error = ET_INVALID_PARAMETER_TYPE);
	if (get_casted_parameter(p, &param[0], &val, PT_U64) != ET_OK)
		return (p->error);
	if (get_type(p, &param[1], &type) != ET_OK)
		return (p->error);
	if (param[2].location != PL_ALIAS
			|| param[2].data.index >= p->func->alias_size)
		return (p->error = ET_INVALID_PARAMETER);
	alias = &p->func->alias_memory[param[2].data.index];
	alias->type = type;
	if ((alias->data.i8 = malloc(val.u64)) == NULL)
		return (p->error = ET_ALLOCATION_FAILED);
	bzero(alias->data.i8, val.u64);
	return (p->error);
}
