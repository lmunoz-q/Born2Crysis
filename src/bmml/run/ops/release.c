/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:47 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_error_type	process_release(t_processor *p, t_op_param *param)
{
	t_entry	*e;
	void	**pp;

	if (param->location == PL_SYMBOL)
	{
		if (param->data.index >= p->func->needed_symbols)
			return (p->error = ET_INVALID_PARAMETER);
		pp = &p->func->symbols[param->data.index].ptr;
	}
	else if (param->location == PL_ALIAS)
	{
		if (param->data.index >= p->func->alias_size)
			return (p->error = ET_INVALID_PARAMETER);
		e = &p->func->alias_memory[param->data.index];
		pp = (void**)&e->data.i8;
	}
	else
		return (p->error = ET_INVALID_PARAMETER_LOCATION);
	free(*pp);
	*pp = NULL;
	return (p->error);
}
