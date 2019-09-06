/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:37:46 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:37:49 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

static t_op_table	*op_table(void)
{
	static t_op_table	table[] = {
	[OC_ALIAS] = {"alias", OC_ALIAS, 4, compile_alias, process_alias},
	[OC_ADD] = {"add", OC_ADD, 3, compile_common_3, process_add},
	[OC_SUB] = {"sub", OC_SUB, 3, compile_common_3, process_sub},
	[OC_MUL] = {"mul", OC_MUL, 3, compile_common_3, process_mul},
	[OC_DIV] = {"div", OC_DIV, 3, compile_common_3, process_div},
	[OC_MOD] = {"mod", OC_MOD, 3, compile_common_3, process_mod},
	[OC_AND] = {"and", OC_AND, 3, compile_common_3, process_and},
	[OC_OR] = {"or", OC_OR, 3, compile_common_3, process_or},
	[OC_XOR] = {"xor", OC_XOR, 3, compile_common_3, process_xor},
	[OC_SU] = {"shift_up", OC_SU, 3, compile_common_3, process_shift_up},
	[OC_SD] = {"shift_down", OC_SD, 3, compile_common_3, process_shift_down},
	[OC_LESS] = {"less", OC_LESS, 3, compile_common_3, process_less},
	[OC_MORE] = {"more", OC_MORE, 3, compile_common_3, process_more},
	[OC_NOT] = {"not", OC_NOT, 2, compile_common_2, process_not},
	[OC_POINT] = {"point", OC_POINT, 2, compile_ptr_move, process_point},
	[OC_DELTA] = {"delta", OC_DELTA, 2, compile_ptr_move, process_delta},
	[OC_SET] = {"set", OC_SET, 2, compile_common_2, process_set},
	[OC_CALL] = {"call", OC_CALL, 2, compile_call, process_call},
	[OC_CALL_IF] = {"call_if", OC_CALL_IF, 3, compile_call_if, process_call_if},
	[OC_RELEASE] = {"release", OC_RELEASE, 1, compile_release, process_release},
	[OC_ALLOCATE] = {"allocate", OC_ALLOCATE, 3, compile_alloc, process_alloc}};

	return (table);
}

t_op_table			*get_op(void *id, int mode)
{
	int					it;

	if (mode == 1)
		return (*(int*)id <= OC_RELEASE ? &op_table()[*(int*)id] : NULL);
	it = 0;
	while (it <= OC_RELEASE && strcmp(op_table()[it].name, id))
		++it;
	return (it <= OC_RELEASE ? &op_table()[it] : NULL);
}
