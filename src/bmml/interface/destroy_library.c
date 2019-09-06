/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_library.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:34 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

void	destroy_library(t_library *lib)
{
	uint64_t	it;

	if ((it = (uint64_t)-1) && lib == NULL)
		return ;
	while (++it < lib->nb_functions)
	{
		free(lib->function_name[it]);
		lib->function_name[it] = NULL;
		destroy_function(&lib->function[it]);
	}
	lib->nb_functions = 0;
	free(lib->function_name);
	lib->function_name = NULL;
	free(lib->function);
	lib->function = NULL;
	it = (uint64_t)-1;
	while (++it < lib->nb_symbols)
	{
		free(lib->symbol[it].name);
		lib->symbol[it].name = NULL;
	}
	lib->nb_symbols = 0;
	free(lib->symbol);
	lib->symbol = NULL;
}
