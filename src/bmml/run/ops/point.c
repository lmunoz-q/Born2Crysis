/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:43 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:46 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_error_type	process_point(t_processor *p, t_op_param *param)
{
	t_data		pos;
	t_ptr_type	type;

	if (get_param_type(p, &param[1], &type) != ET_OK || type != PT_U64
			|| get_casted_parameter(p, &param[1], &pos, PT_U64) != ET_OK)
		return (p->error);
	if (param[0].location != PL_ALIAS)
		return (p->error = ET_INVALID_PARAMETER_LOCATION);
	if (param[0].data.index >= p->func->alias_size)
		return (p->error = ET_INVALID_PARAMETER);
	p->func->alias_memory[param[0].data.index].data.p = (void*)pos.u64;
	return (p->error);
}
