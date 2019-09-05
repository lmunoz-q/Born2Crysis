/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:40:32 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:40:34 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

static inline void	i_su(t_data_ptr ptr, t_ptr_type type, t_data val1,
	t_data val2)
{
	if (type == PT_I8)
		*ptr.i8 = val1.i8 << val2.i8;
	if (type == PT_I16)
		*ptr.i16 = val1.i16 << val2.i16;
	if (type == PT_I32)
		*ptr.i32 = val1.i32 << val2.i32;
	if (type == PT_I64)
		*ptr.i64 = val1.i64 << val2.i64;
	if (type == PT_U8)
		*ptr.u8 = val1.u8 << val2.u8;
	if (type == PT_U16)
		*ptr.u16 = val1.u16 << val2.u16;
	if (type == PT_U32)
		*ptr.u32 = val1.u32 << val2.u32;
	if (type == PT_U64)
		*ptr.u64 = val1.u64 << val2.u64;
}

t_error_type		process_shift_up(t_processor *p, t_op_param *param)
{
	t_data_ptr	ptr;
	t_ptr_type	type;
	t_data		val1;
	t_data		val2;

	if (get_ptr(p, &param[0], &ptr, PT_ANY) != ET_OK)
		return (p->error);
	if (get_param_type(p, &param[0], &type) != ET_OK)
		return (p->error);
	if (type == PT_F32 || type == PT_F64)
		return (p->error = ET_INVALID_PARAMETER_TYPE);
	if (get_casted_parameter(p, &param[1], &val1, type) != ET_OK)
		return (p->error);
	if (get_casted_parameter(p, &param[2], &val2, type) != ET_OK)
		return (p->error);
	i_su(ptr, type, val1, val2);
	return (p->error);
}
