/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:01 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:03 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

int			write_op(t_compiler *comp, t_op_code code, t_op_param *parameters,
						int nb_param)
{
	t_function	*func;
	uint64_t	len;

	len = sizeof(t_op_param) * nb_param;
	func = comp->cur_func;
	if ((func->code = realloc_f(func->code, func->code_size + len + 1)) == NULL)
	{
		set_error(comp, ET_COULD_NOT_WRITE_OPERATION);
		return (-1);
	}
	func->code[func->code_size++] = code;
	memcpy(&func->code[func->code_size], parameters, len);
	func->code_size += len;
	return (0);
}
