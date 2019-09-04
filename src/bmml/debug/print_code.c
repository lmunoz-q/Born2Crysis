/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:08 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:09 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

int			print_code(t_function *func)
{
	uint64_t	it;
	int			i;
	int			op_code;
	t_op_table	*opt;

	if (func == NULL)
		return (0);
	it = 0;
	while (it < func->code_size)
	{
		op_code = func->code[it++];
		if ((opt = get_op(&op_code, 1)) == NULL)
			return (printf("KABUUUM\n"));
		printf("op: '%s' at %p\n", opt->name, &func->code[it]);
		i = -1;
		while (++i < (int)opt->nb_param)
		{
			print_param(&func->code[it], func);
			it += sizeof(t_op_param);
		}
	}
	return (0);
}
