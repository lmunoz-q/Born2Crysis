/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmml.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 15:42:00 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/01 15:42:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMML_H
# define BMML_H

# include <bmml_structs.h>

t_error_type	init_function(t_function *func);
t_error_type	compile_function(const char *text, t_function *func, int debug);

t_error_type	init_library(t_library *lib);
t_error_type	add_function_to_library(t_library *lib, const char *name,
										t_function *func, int debug);
t_error_type	add_function_to_library_direct(t_library *lib, const char *name,
												const char *text, int debug);
t_error_type	add_extern_function_to_library(t_library *lib, const char *name,
						t_error_type (*f)(t_processor *caller, char *param));
t_error_type	add_address_to_library(t_library *lib, const char *name,
										char *ptr);
t_error_type	link_library(t_library *lib, int debug);
t_function		*get_function(t_library *lib, const char *name);

t_error_type	execute_function(t_function *func, void *param, void *local,
								int debug);

int				print_code(t_function *func);

void			destroy_function(t_function *func);
void			destroy_library(t_library *lib);

#endif
