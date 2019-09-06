/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:21 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_error_type	process_call(t_processor *p, t_op_param *param)
{
	t_symbol_data	sym;
	t_data_ptr		ptr;

	if (get_ptr(p, &param[1], &ptr, PT_ANY) != ET_OK)
		return (p->error);
	if (param[0].location != PL_SYMBOL)
		return (p->error = ET_INVALID_PARAMETER_LOCATION);
	if (param[0].data.index >= p->func->needed_symbols)
		return (p->error = ET_INVALID_PARAMETER);
	sym = p->func->symbols[param[0].data.index];
	if (sym.type == ST_FUNCTION)
		execute_function(sym.ptr, ptr.i8, p->func->alias_memory[1].data.i8,
			p->debug);
	else if (sym.type == ST_EXTERN_FUNCTION)
		((t_error_type(*)(t_processor*, char*))sym.ptr)(p, (char*)ptr.i8);
	else
		p->error = ET_INVALID_PARAMETER_TYPE;
	return (p->error);
}
