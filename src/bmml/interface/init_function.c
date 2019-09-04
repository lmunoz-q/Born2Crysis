/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:41 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:43 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_error_type	init_function(t_function *func)
{
	func->alias_memory = malloc(sizeof(t_entry) * 2);
	if (func->alias_memory == NULL)
		return (ET_ALLOCATION_FAILED);
	func->alias_memory[0] = (t_entry){.type = PT_I8, .data = {.i8 = NULL}};
	func->alias_memory[1] = (t_entry){.type = PT_I8, .data = {.i8 = NULL}};
	func->alias_size = 2;
	func->symbols = NULL;
	func->needed_symbols = 0;
	func->code_size = 0;
	func->code = NULL;
	return (ET_OK);
}
