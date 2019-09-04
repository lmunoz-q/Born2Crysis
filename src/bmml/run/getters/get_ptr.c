/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:06 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:07 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** will TRY to extract a pointer of a given type from the parameter
** note: symbols are always char*
*/

t_error_type	get_ptr(t_processor *p, t_op_param *param, t_data_ptr *ptr,
						t_ptr_type type)
{
	t_entry	*e;

	if (param->location == PL_SYMBOL)
	{
		if (param->data.index >= p->func->needed_symbols)
			return (p->error = ET_INVALID_PARAMETER);
		ptr->i8 = p->func->symbols[param->data.index].ptr;
	}
	else if (param->location == PL_ALIAS)
	{
		if (param->data.index >= p->func->alias_size)
			return (p->error = ET_INVALID_PARAMETER);
		e = &p->func->alias_memory[param->data.index];
		if (type != PT_ANY && e->type != type)
			return (p->error = ET_INVALID_PARAMETER_TYPE);
		ptr->i8 = e->data.i8;
	}
	else
		return (p->error = ET_INVALID_PARAMETER_LOCATION);
	return (ET_OK);
}
