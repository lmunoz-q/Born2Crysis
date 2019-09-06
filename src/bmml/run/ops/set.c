/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:49 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:51 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

static inline void	i_set(t_data_ptr ptr, t_ptr_type type, t_data val)
{
	if (type == PT_I8)
		*ptr.i8 = val.i8;
	if (type == PT_I16)
		*ptr.i16 = val.i16;
	if (type == PT_I32)
		*ptr.i32 = val.i32;
	if (type == PT_I64)
		*ptr.i64 = val.i64;
	if (type == PT_U8)
		*ptr.u8 = val.u8;
	if (type == PT_U16)
		*ptr.u16 = val.u16;
	if (type == PT_U32)
		*ptr.u32 = val.u32;
	if (type == PT_U64)
		*ptr.u64 = val.u64;
	if (type == PT_F32)
		*ptr.f32 = val.f32;
	if (type == PT_F64)
		*ptr.f64 = val.f64;
}

t_error_type		process_set(t_processor *p, t_op_param *param)
{
	t_data_ptr	ptr;
	t_ptr_type	type;
	t_data		val;

	if (get_ptr(p, &param[0], &ptr, PT_ANY) != ET_OK)
		return (p->error);
	if (get_param_type(p, &param[0], &type) != ET_OK)
		return (p->error);
	if (get_casted_parameter(p, &param[1], &val, type) != ET_OK)
		return (p->error);
	i_set(ptr, type, val);
	return (p->error);
}
