/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:10 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:13 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

void		print_entry(t_entry e)
{
	printf("%s.%p.", (char*[]){"i8", "u8", "i16", "u16", "i32", "u32", "i64", "u64", "f32", "f64"}[e.type], e.data.i8);
	if (e.data.i8 != NULL)
		switch (e.type)
		{
			case PT_I8: printf("%hhi\n", *e.data.i8); break;
			case PT_U8: printf("%hhu\n", *e.data.u8); break;
			case PT_I16: printf("%hi\n", *e.data.i16); break;
			case PT_U16: printf("%hu\n", *e.data.u16); break;
			case PT_I32: printf("%i\n", *e.data.i32); break;
			case PT_U32: printf("%u\n", *e.data.u32); break;
			case PT_I64: printf("%lli\n", (long long)*e.data.i64); break;
			case PT_U64: printf("%llu\n", (unsigned long long)*e.data.u64); break;
			case PT_F32: printf("%f\n", *e.data.f32); break;
			case PT_F64: printf("%f\n", *e.data.f64); break;
			case PT_ANY: printf("%hhi\n", *e.data.i8); break;
		}
	else
		printf("(void)\n");
}
