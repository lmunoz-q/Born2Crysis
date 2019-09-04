/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:38:23 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:38:24 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** either find a valid alias or symbol or prepare a new unresolved symbol
** might return (uint64_t)-1 on memory reallocation error
*/

uint64_t	find_name(t_compiler *comp, const char *name,
						int8_t *location)
{
	uint64_t	it;
	t_function	*func;

	it = 0;
	func = comp->cur_func;
	while (it < func->alias_size && strcmp(comp->alias_names[it], name))
		++it;
	if (it < func->alias_size)
	{
		*location = PL_ALIAS;
		return (it);
	}
	*location = PL_SYMBOL;
	it = 0;
	while (it < func->needed_symbols && strcmp(func->symbols[it].name, name))
		++it;
	if (it < func->needed_symbols)
		return (it);
	if ((func->symbols = realloc_f(func->symbols,
					sizeof(t_symbol_data) * ++func->needed_symbols)) == NULL)
		return ((uint64_t)-1);
	if ((func->symbols[func->needed_symbols - 1] = (t_symbol_data)
		{.name = strdup(comp->head), .ptr = NULL}).name == NULL)
		return ((uint64_t)-1 | --func->needed_symbols);
	return (func->needed_symbols - 1);
}
