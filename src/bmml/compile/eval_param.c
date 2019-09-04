/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:38:15 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:38:18 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_op_param	eval_param(t_compiler *comp)
{
	int			it;
	char		*t;
	t_op_param	out;
	const char	*types[] = {"u8", "i8", "u16", "i16", "u32", "i32", "u64",
		"i64", "f32", "f64"};

	it = PT_I8;
	while (it <= PT_F64 && strcmp(types[it], comp->head))
		++it;
	if (it <= PT_F64)
		return ((t_op_param){PL_IMMEDIATE, OPT_TYPE, {.type = it}});
	out = (t_op_param){PL_IMMEDIATE, OPT_INTEGER, {.i = strtoll(comp->head, &t,
																0)}};
	if (*t == '\0')
		return (out);
	out.type = OPT_FLOAT;
	out.data.f = strtod(comp->head, &t);
	if (*t == '\0')
		return (out);
	out.type = OPT_INTEGER;
	if ((out.data.index = find_name(comp, comp->head, &out.location))
			== (uint64_t) - 1)
		set_error(comp, ET_ALLOCATION_FAILED);
	return (out);
}
