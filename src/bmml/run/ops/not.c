/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:39 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:43 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

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

t_error_type		process_not(t_processor *p, t_op_param *param)
{
	t_data_ptr	ptr;
	t_ptr_type	type1;
	t_ptr_type	type2;
	t_data		val;
	int			bol;

	if (get_ptr(p, &param[0], &ptr, PT_ANY) != ET_OK)
		return (p->error);
	if (get_param_type(p, &param[0], &type1) != ET_OK)
		return (p->error);
	if (get_param_type(p, &param[1], &type2) != ET_OK)
		return (p->error);
	if (get_casted_parameter(p, &param[1], &val, type2) != ET_OK)
		return (p->error);
	bol = 0;
	if (type2 == PT_I8 || type2 == PT_U8)
		bol = !val.u8;
	if (type2 == PT_I16 || type2 == PT_U16)
		bol = !val.u16;
	if (type2 == PT_I32 || type2 == PT_U32 || type2 == PT_F32)
		bol = !val.u32;
	if (type2 == PT_I64 || type2 == PT_U64 || type2 == PT_F64)
		bol = !val.u64;
	i_set(ptr, type1, bol);
	return (p->error);
}
