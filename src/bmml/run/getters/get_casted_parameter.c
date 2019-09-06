/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_casted_parameter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:57 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:59 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

/*
** extract a parameter of the chosen type (immediate and alias are casted)
*/

static inline t_data	cast_up(t_data_ptr val, t_ptr_type type)
{
	t_data	data;

	data.i64 = 0;
	if (type == PT_I8)
		data.i64 = (int64_t)*val.i8;
	if (type == PT_I16)
		data.i64 = (int64_t)*val.i16;
	if (type == PT_I32)
		data.i64 = (int64_t)*val.i32;
	if (type == PT_I64)
		data.i64 = *val.i64;
	if (type == PT_U8)
		data.u64 = (uint64_t)*val.u8;
	if (type == PT_U16)
		data.u64 = (uint64_t)*val.u16;
	if (type == PT_U32)
		data.u64 = (uint64_t)*val.u32;
	if (type == PT_U64)
		data.u64 = *val.u64;
	if (type == PT_F32)
		data.f64 = (double)*val.f32;
	if (type == PT_F64)
		data.f64 = *val.f64;
	return (data);
}

static inline t_data	cast_down(t_data data, t_ptr_type type)
{
	if (type == PT_I8)
		data.i8 = (int8_t)data.i64;
	if (type == PT_I16)
		data.i16 = (int16_t)data.i64;
	if (type == PT_I32)
		data.i32 = (int32_t)data.i64;
	if (type == PT_U8)
		data.u8 = (uint8_t)data.u64;
	if (type == PT_U16)
		data.u16 = (uint16_t)data.u64;
	if (type == PT_U32)
		data.u32 = (uint32_t)data.u64;
	if (type == PT_F32)
		data.f32 = (float)data.f64;
	return (data);
}

static inline void		cast_max(t_ptr_type type_in, t_ptr_type type_out,
									t_ptr_type *ti, t_ptr_type *to)
{
	*ti = type_in;
	if (type_in == PT_I8 || type_in == PT_I16 || type_in == PT_I32)
		*ti = PT_I64;
	else if (type_in == PT_U8 || type_in == PT_U16 || type_in == PT_U32)
		*ti = PT_U64;
	else if (type_in == PT_F32)
		*ti = PT_F64;
	*to = type_out;
	if (type_out == PT_I8 || type_out == PT_I16 || type_out == PT_I32)
		*to = PT_I64;
	else if (type_out == PT_U8 || type_out == PT_U16 || type_out == PT_U32)
		*to = PT_U64;
	else if (type_out == PT_F32)
		*to = PT_F64;
}

t_data					cast(void *val, t_ptr_type type_in, t_ptr_type type_out)
{
	t_data		data;
	t_ptr_type	ti;
	t_ptr_type	to;
	t_data_ptr	ptr;

	ptr.i8 = val;
	data = cast_up(ptr, type_in);
	cast_max(type_in, type_out, &ti, &to);
	if (ti == PT_I64 && to == PT_U64)
		data.u64 = (uint64_t)data.i64;
	if (ti == PT_I64 && to == PT_F64)
		data.f64 = (double)data.i64;
	if (ti == PT_U64 && to == PT_I64)
		data.i64 = (int64_t)data.u64;
	if (ti == PT_U64 && to == PT_F64)
		data.f64 = (double)data.u64;
	if (ti == PT_F64 && to == PT_I64)
		data.i64 = (int64_t)data.f64;
	if (ti == PT_F64 && to == PT_U64)
		data.u64 = (uint64_t)data.f64;
	return (cast_down(data, type_out));
}

t_error_type			get_casted_parameter(t_processor *p, t_op_param *param,
									t_data *val, t_ptr_type type)
{
	if (param->location == PL_SYMBOL)
	{
		if (param->data.index >= p->func->needed_symbols)
			return (p->error = ET_INVALID_PARAMETER);
		if (p->func->symbols[param->data.index].type != ST_POINTER)
			return (p->error = ET_INVALID_SYMBOL_TYPE);
		*val = cast(p->func->symbols[param->data.index].ptr, PT_I8, type);
	}
	else if (param->location == PL_IMMEDIATE)
		if (param->type == OPT_INTEGER)
			*val = cast(&param->data, PT_I64, type);
		else if (param->type == OPT_FLOAT)
			*val = cast((t_data_ptr*)&param->data, PT_F64, type);
		else
			return (p->error = ET_INVALID_PARAMETER_TYPE);
	else if (param->location == PL_ALIAS)
	{
		if (param->data.index >= p->func->alias_size)
			return (p->error = ET_INVALID_PARAMETER);
		*val = cast(p->func->alias_memory[param->data.index].data.i8,
			p->func->alias_memory[param->data.index].type, type);
	}
	else
		return (p->error = ET_INVALID_PARAMETER_LOCATION);
	return (ET_OK);
}
