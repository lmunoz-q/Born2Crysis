/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_symbol_to_library.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:31 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:32 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_error_type	add_address_to_library(t_library *lib, const char *name,
										char *ptr)
{
	uint64_t	it;

	it = 0;
	while (it < lib->nb_symbols && strcmp(lib->symbol[it].name, name))
		++it;
	if (it < lib->nb_symbols)
		return (ET_DUPLICATE_SYMBOL);
	it = 0;
	while (it < lib->nb_functions && strcmp(lib->function_name[it], name))
		++it;
	if (it < lib->nb_functions)
		return (ET_DUPLICATE_SYMBOL);
	if ((lib->symbol = realloc_f(lib->symbol,
			sizeof(t_symbol_data) * (1 + lib->nb_symbols))) == NULL)
		return (ET_ALLOCATION_FAILED);
	if ((lib->symbol[lib->nb_symbols].name = strdup(name)) == NULL)
		return (ET_ALLOCATION_FAILED);
	lib->symbol[lib->nb_symbols].type = ST_POINTER;
	lib->symbol[lib->nb_symbols++].ptr = ptr;
	return (ET_OK);
}
