/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:17 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:18 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_error_type	process_alias(t_processor *p, t_op_param *param)
{
	t_entry		*alias;
	t_ptr_type	type;
	int64_t		delta;
	t_data_ptr	ptr;

	if (get_ptr(p, &param[0], &ptr, PT_ANY) != ET_OK)
		return (p->error);
	if (get_int64(p, &param[1], &delta) != ET_OK)
		return (p->error);
	if (get_type(p, &param[2], &type) != ET_OK)
		return (p->error);
	if (param[3].location != PL_ALIAS
			|| param[3].data.index >= p->func->alias_size)
		return (p->error = ET_INVALID_PARAMETER);
	alias = &p->func->alias_memory[param[3].data.index];
	alias->type = type;
	alias->data.i8 = &ptr.i8[delta];
	return (p->error);
}
