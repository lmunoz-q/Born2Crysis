/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_library.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:46 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:48 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

static inline int			link_function_0(t_library *lib, t_function *func,
											uint64_t sym, int debug)
{
	uint64_t	it;

	it = 0;
	while (it < lib->nb_functions
			&& strcmp(lib->function_name[it], func->symbols[sym].name))
		++it;
	if (it < lib->nb_functions)
	{
		func->symbols[sym].ptr = &lib->function[it];
		if (func->symbols[sym].type != ST_UNASSIGNED && debug)
			printf("Linker warning: relinked symbol: '%s'\n",
				func->symbols[sym].name);
		func->symbols[sym].type = ST_FUNCTION;
		return (1);
	}
	return (0);
}

static inline t_error_type	link_function(t_library *lib, t_function *func,
											char **sym_name, int debug)
{
	uint64_t	sym;
	uint64_t	it;

	sym = (uint64_t)-1;
	while (++sym < func->needed_symbols && !(it = 0))
	{
		while (it < lib->nb_symbols
				&& strcmp(lib->symbol[it].name, func->symbols[sym].name))
			++it;
		if (it < lib->nb_symbols)
		{
			func->symbols[sym].ptr = lib->symbol[it].ptr;
			if (func->symbols[sym].type != ST_UNASSIGNED && debug)
				printf("Linker warning: relinked symbol: '%s'\n",
					func->symbols[sym].name);
			func->symbols[sym].type = lib->symbol[it].type;
			continue;
		}
		if (link_function_0(lib, func, sym, debug))
			continue ;
		*sym_name = func->symbols[sym].name;
		return (ET_UNDECLARED_SYMBOL);
	}
	return (ET_OK);
}

/*
** resolve symbols and function names
*/

t_error_type				link_library(t_library *lib, int debug)
{
	uint64_t		it;
	t_error_type	r;
	char			*sym;

	it = (uint64_t)-1;
	while (++it < lib->nb_functions)
		if ((r = link_function(lib, &lib->function[it], &sym, debug)) != ET_OK)
		{
			if (debug)
				printf("Linker error: Missing symbol '%s' in function '%s'\n",
					sym, lib->function_name[it]);
			return (r);
		}
	return (ET_OK);
}
