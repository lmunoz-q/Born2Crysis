/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 22:43:24 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/09/06 11:45:16 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map_file.h>
#include <bmml_functions.h>

static inline Uint8	*load_lib_1(Uint8 *ptr, t_library *lib, t_function func)
{
	uint64_t	i;

	i = (uint64_t)-1;
	while (++i < func.alias_size)
		func.alias_memory[i] = (t_entry){.type = *ptr++, .data = {NULL}};
	i = (uint64_t)-1;
	while (++i < func.needed_symbols)
	{
		func.symbols[i] = (t_symbol_data){.name = strdup((char*)ptr),
			.ptr = NULL};
		if (func.symbols[i].name == NULL)
		{
			free(lib->function_name[lib->nb_functions]);
			free(func.symbols);
			free(func.alias_memory);
			free(func.code);
			return (NULL);
		}
		ptr += 12;
	}
	lib->function[lib->nb_functions++] = func;
	return (ptr);
}

static inline Uint8	*load_lib_0(Uint8 *ptr, t_library *lib)
{
	t_function	func;

	func = (t_function){.code_size = 0};
	if ((lib->function_name[lib->nb_functions] = mf_strdup((char*)ptr))
		== NULL)
		return (NULL);
	ptr += 12;
	mf_memcpy(&func, ptr, 24);
	ptr += 24;
	if ((func.symbols = malloc(sizeof(t_symbol_data) * func.needed_symbols))
		== NULL
		|| (func.alias_memory = malloc(sizeof(t_entry) * func.alias_size))
		== NULL
		|| (func.code = malloc(sizeof(char) * func.code_size)) == NULL)
	{
		free(lib->function_name[lib->nb_functions]);
		free(func.symbols);
		free(func.alias_memory);
		return (NULL);
	}
	mf_memcpy(func.code, ptr, func.code_size);
	ptr += func.code_size;
	return (load_lib_1(ptr, lib, func));
}

Uint8				*load_lib(Uint8 *ptr, t_library *lib, uint64_t c)
{
	if ((lib->function = realloc_f(lib->function,
			(lib->nb_functions + c) * sizeof(t_function))) == NULL)
		return (NULL);
	if ((lib->function_name = realloc_f(lib->function_name,
		(lib->nb_functions + c) * sizeof(char*))) == NULL)
	{
		free(lib->function);
		lib->function = NULL;
		return (NULL);
	}
	while (c--)
		ptr = load_lib_0(ptr, lib);
	return (ptr);
}
