/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_alias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:38:32 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:38:34 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** insert a new alias pointer in the list, test if symbol already exists
** return the index of the created alias, -1 on memory error/duplicate
*/

static inline uint64_t	insert_alias(t_compiler *comp, const char *name)
{
	if ((comp->alias_names = realloc_f(comp->alias_names,
		(1 + comp->cur_func->alias_size) * sizeof(char*))) == NULL)
	{
		set_error(comp, ET_ALLOCATION_FAILED);
		return ((uint64_t)-1);
	}
	if ((comp->alias_names[comp->cur_func->alias_size] = strdup(name)) == NULL)
	{
		set_error(comp, ET_ALLOCATION_FAILED);
		return ((uint64_t)-1);
	}
	if ((comp->cur_func->alias_memory = realloc_f(comp->cur_func->alias_memory,
		(1 + comp->cur_func->alias_size) * sizeof(t_entry))) == NULL)
	{
		set_error(comp, ET_ALLOCATION_FAILED);
		return ((uint64_t)-1);
	}
	comp->cur_func->alias_memory[comp->cur_func->alias_size] = (t_entry){
		.type = PT_I8, .data = {.i8 = NULL}};
	return (comp->cur_func->alias_size++);
}

uint64_t				new_alias(t_compiler *comp, const char *name)
{
	uint64_t	it;
	t_function	*func;

	func = comp->cur_func;
	it = 0;
	while (it < func->needed_symbols && strcmp(func->symbols[it].name, name))
		++it;
	if (it < func->needed_symbols)
	{
		set_error(comp, ET_ALIAS_NAME_TAKEN);
		return ((uint64_t)-1);
	}
	it = 0;
	while (it < func->alias_size && strcmp(comp->alias_names[it], name))
		++it;
	if (it < func->needed_symbols)
	{
		set_error(comp, ET_ALIAS_NAME_TAKEN);
		return ((uint64_t)-1);
	}
	return (insert_alias(comp, name));
}
