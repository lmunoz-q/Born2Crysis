/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:39 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:40 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_function	*get_function(t_library *lib, const char *name)
{
	uint64_t	it;

	it = 0;
	while (it < lib->nb_functions && strcmp(lib->function_name[it], name))
		++it;
	return (it < lib->nb_functions ? &lib->function[it] : NULL);
}
