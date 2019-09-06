/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_function_to_library_direct.h                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 15:42:00 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/01 15:42:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_error_type	add_function_to_library_direct(t_library *lib, const char *name,
												const char *text, int debug)
{
	t_function		func;
	t_error_type	err;

	init_function(&func);
	if ((err = compile_function(text, &func, debug)) != ET_OK)
		return (err);
	return (add_function_to_library(lib, name, &func, debug));
}
