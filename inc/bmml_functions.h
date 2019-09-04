/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmml_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:35:59 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:36:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMML_FUNCTIONS_H
# define BMML_FUNCTIONS_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# include <bmml.h>

void			*realloc_f(void *p, size_t size);

void			print_entry(t_entry e);
void			print_param(char *code, t_function *func);
t_compiler		*set_error(t_compiler *comp, t_error_type type);
void			error(t_compiler *comp);
t_error_type	finish_compilation(t_compiler *comp, int debug);
uint64_t		find_name(t_compiler *comp, const char *name,
					int8_t *location);
t_op_param		eval_param(t_compiler *comp);
t_op_param		*eval_params(t_compiler *comp, int nb_param);
uint64_t		new_alias(t_compiler *comp, const char *name);
int				write_op(t_compiler *comp, t_op_code code,
							t_op_param *parameters, int nb_param);

t_error_type	compile_alias(int ins, t_compiler *comp);
t_error_type	compile_alloc(int ins, t_compiler *comp);
t_error_type	compile_ptr_move(int ins, t_compiler *comp);
t_error_type	compile_common_2(int ins, t_compiler *comp);
t_error_type	compile_common_3(int ins, t_compiler *comp);
t_error_type	compile_call(int ins, t_compiler *comp);
t_error_type	compile_call_if(int ins, t_compiler *comp);
t_error_type	compile_release(int ins, t_compiler *comp);

t_op_table		*get_op(void *id, int mode);
t_compiler		*compile_line(t_compiler *comp);

/*
** uint8_t var = 3;
** ALIAS.TYPE.2 -> i8.&var
** get_type: retrieve the data as type (in the above case: 3: u16)
** get_param_type: actual type of the parameter (in the case above: i8)
** IMMEDIATE.TYPE.i32
** get_type: i32
** get_param_type: invalid
** IMMEDIATE.FLOAT.3,14
** get_type: invalid
** get_param_type: f64
*/

t_error_type	get_type(t_processor *p, t_op_param *param, t_ptr_type *type);
t_error_type	get_param_type(t_processor *p, t_op_param *param,
								t_ptr_type *type);
t_error_type	get_ptr(t_processor *p, t_op_param *param, t_data_ptr *ptr,
						t_ptr_type type);
t_error_type	get_int64(t_processor *p, t_op_param *param, int64_t *integer);
t_error_type	get_float64(t_processor *p, t_op_param *param, double *flt);
t_error_type	get_casted_parameter(t_processor *p, t_op_param *param,
											t_data *val, t_ptr_type type);

t_data			cast(void *val, t_ptr_type type_in, t_ptr_type type_out);

t_error_type	process_alias(t_processor *proc, t_op_param *param);
t_error_type	process_add(t_processor *p, t_op_param *param);
t_error_type	process_sub(t_processor *p, t_op_param *param);
t_error_type	process_mul(t_processor *p, t_op_param *param);
t_error_type	process_div(t_processor *p, t_op_param *param);
t_error_type	process_mod(t_processor *p, t_op_param *param);
t_error_type	process_less(t_processor *p, t_op_param *param);
t_error_type	process_more(t_processor *p, t_op_param *param);
t_error_type	process_not(t_processor *p, t_op_param *param);
t_error_type	process_set(t_processor *p, t_op_param *param);
t_error_type	process_point(t_processor *p, t_op_param *param);
t_error_type	process_delta(t_processor *p, t_op_param *param);
t_error_type	process_call(t_processor *p, t_op_param *param);
t_error_type	process_call_if(t_processor *p, t_op_param *param);
t_error_type	process_alloc(t_processor *p, t_op_param *param);
t_error_type	process_release(t_processor *p, t_op_param *param);
t_error_type	process_and(t_processor *p, t_op_param *param);
t_error_type	process_or(t_processor *p, t_op_param *param);
t_error_type	process_xor(t_processor *p, t_op_param *param);
t_error_type	process_shift_up(t_processor *p, t_op_param *param);
t_error_type	process_shift_down(t_processor *p, t_op_param *param);

#endif
