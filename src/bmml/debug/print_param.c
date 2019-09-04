/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:14 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:16 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

void		print_param(char *code, t_function *func)
{
	t_op_param	*p;
	t_entry		e;

	p = (t_op_param*)code;
	printf("%s.", (char*[]){"IMMEDIATE", "ALIAS", "SYMBOL"}[p->location]);
	printf("%s.", (char*[]){"INTEGER", "FLOAT", "TYPE"}[p->type]);
	if (p->location == PL_IMMEDIATE)
		switch (p->type)
		{
			case OPT_INTEGER: printf("%lli\n", (long long)p->data.i); break ;
			case OPT_FLOAT: printf("%f\n", p->data.f); break ;
			case OPT_TYPE: printf("%s\n", (char*[]){"i8", "u8", "i16", "u16", "i32", "u32", "i64", "u64", "f32", "f64"}[p->data.type]); break ;
		}
	else if (p->location == PL_ALIAS)
	{
		e = func->alias_memory[p->data.index];
		printf("%llu -> ", (unsigned long long)p->data.index);
		print_entry(e);
	}
	else
		printf("%llu -> {'%s': %p}\n", (unsigned long long)p->data.index, func->symbols[p->data.index].name, func->symbols[p->data.index].ptr);
}
