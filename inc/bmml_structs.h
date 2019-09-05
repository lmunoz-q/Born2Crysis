/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmml_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:36:02 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:36:04 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMML_STRUCTS_H
# define BMML_STRUCTS_H

# include <bmml_constants.h>
# include <bmml_types.h>

union	u_data
{
	int8_t			i8;
	uint8_t			u8;
	int16_t			i16;
	uint16_t		u16;
	int32_t			i32;
	uint32_t		u32;
	int64_t			i64;
	uint64_t		u64;
	float			f32;
	double			f64;
};

union	u_data_ptr
{
	int8_t			*i8;
	uint8_t			*u8;
	int16_t			*i16;
	uint16_t		*u16;
	int32_t			*i32;
	uint32_t		*u32;
	int64_t			*i64;
	uint64_t		*u64;
	float			*f32;
	double			*f64;
	void			*p;
};

struct	s_entry
{
	t_ptr_type		type;
	t_data_ptr		data;
};

union	u_op_param_data
{
	uint64_t	index;
	int64_t		i;
	double		f;
	t_ptr_type	type;
};

# pragma pack(push, 1)

struct	s_op_param
{
	int8_t			location;
	int8_t			type;
	t_op_param_data	data;
};

struct	s_op
{
	uint8_t		code;
	t_op_param	param[];
};

# pragma pack(pop)

struct	s_symbol_data
{
	char			*name;
	void			*ptr;
	t_symbol_type	type;
};

struct	s_function
{
	uint64_t		code_size;
	uint64_t		alias_size;
	uint64_t		needed_symbols;
	char			*code;
	t_entry			*alias_memory;
	t_symbol_data	*symbols;
};

struct	s_processor
{
	uint64_t		pc;
	t_function		*func;
	t_error_type	error;
	int				debug;
	char			locale_memory[LOCALE_MEMORY_SIZE];
};

struct	s_error
{
	uint64_t		pos;
	t_error_type	type;
};

struct	s_compiler
{
	char			*text;
	char			*head;
	t_function		*cur_func;
	char			**alias_names;
	t_error			error;
};

struct	s_op_table
{
	char			*name;
	t_op_code		code;
	uint64_t		nb_param;
	t_error_type	(*compile)(int ins, t_compiler *comp);
	t_error_type	(*process)(t_processor *proc, t_op_param *params);
};

struct	s_library
{
	uint64_t		nb_functions;
	uint64_t		nb_symbols;
	char			**function_name;
	t_function		*function;
	t_symbol_data	*symbol;
};

#endif
