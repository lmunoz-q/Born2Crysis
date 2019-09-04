/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:30 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:32 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

static inline int	i_less(t_ptr_type type, t_data val1, t_data val2)
{
	if (type == PT_I8)
		return (val1.i8 < val2.i8);
	if (type == PT_I16)
		return (val1.i16 < val2.i16);
	if (type == PT_I32)
		return (val1.i32 < val2.i32);
	if (type == PT_I64)
		return (val1.i64 < val2.i64);
	if (type == PT_U8)
		return (val1.u8 < val2.u8);
	if (type == PT_U16)
		return (val1.u16 < val2.u16);
	if (type == PT_U32)
		return (val1.u32 < val2.u32);
	if (type == PT_U64)
		return (val1.u64 < val2.u64);
	if (type == PT_F32)
		return (val1.f32 < val2.f32);
	if (type == PT_F64)
		return (val1.f64 < val2.f64);
	return (0);
}

static inline void	i_set(t_data_ptr ptr, t_ptr_type type, int bol)
{
	if (type == PT_I8)
		*ptr.i8 = (int8_t)bol;
	if (type == PT_I16)
		*ptr.i16 = (int16_t)bol;
	if (type == PT_I32)
		*ptr.i32 = (int32_t)bol;
	if (type == PT_I64)
		*ptr.i64 = (int64_t)bol;
	if (type == PT_U8)
		*ptr.u8 = (uint8_t)bol;
	if (type == PT_U16)
		*ptr.u16 = (uint16_t)bol;
	if (type == PT_U32)
		*ptr.u32 = (uint32_t)bol;
	if (type == PT_U64)
		*ptr.u64 = (uint64_t)bol;
	if (type == PT_F32)
		*ptr.f32 = (float)bol;
	if (type == PT_F64)
		*ptr.f64 = (double)bol;
}

t_error_type		process_less(t_processor *p, t_op_param *param)
{
	t_data_ptr	ptr;
	t_ptr_type	type1;
	t_ptr_type	type2;
	t_data		val1;
	t_data		val2;

	if (get_ptr(p, &param[0], &ptr, PT_ANY) != ET_OK)
		return (p->error);
	if (get_param_type(p, &param[1], &type1) != ET_OK)
		return (p->error);
	if (get_param_type(p, &param[2], &type2) != ET_OK)
		return (p->error);
	if (type1 < type2)
		type1 = type2;
	if (get_param_type(p, &param[0], &type2) != ET_OK)
		return (p->error);
	if (get_casted_parameter(p, &param[1], &val1, type1) != ET_OK)
		return (p->error);
	if (get_casted_parameter(p, &param[2], &val2, type1) != ET_OK)
		return (p->error);
	i_set(ptr, type2, i_less(type1, val1, val2));
	return (p->error);
}
