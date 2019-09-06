/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_library.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:44 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_error_type	init_library(t_library *lib)
{
	lib->nb_functions = 0;
	lib->nb_symbols = 0;
	lib->function = NULL;
	lib->function_name = NULL;
	lib->symbol = NULL;
	return (ET_OK);
}
