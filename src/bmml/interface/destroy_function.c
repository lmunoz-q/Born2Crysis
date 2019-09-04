/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:34 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:35 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

void	destroy_function(t_function *func)
{
	uint64_t	it;

	if (func == NULL)
		return ;
	free(func->code);
	func->code = NULL;
	func->code_size = 0;
	free(func->alias_memory);
	func->alias_memory = NULL;
	func->alias_size = 0;
	it = (uint64_t)-1;
	while (++it < func->needed_symbols)
	{
		free(func->symbols[it].name);
		func->symbols[it].name = NULL;
	}
	free(func->symbols);
	func->symbols = NULL;
	func->needed_symbols = 0;
}
