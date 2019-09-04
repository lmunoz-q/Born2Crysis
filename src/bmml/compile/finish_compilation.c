/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_compilation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:38:25 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:38:27 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_error_type	finish_compilation(t_compiler *comp, int debug)
{
	uint64_t	it;

	if (debug)
		error(comp);
	free(comp->text);
	comp->text = NULL;
	comp->head = NULL;
	it = (uint64_t)-1;
	while (++it < comp->cur_func->alias_size)
	{
		free(comp->alias_names[it]);
		comp->alias_names[it] = NULL;
	}
	free(comp->alias_names);
	comp->alias_names = NULL;
	if (comp->error.type == ET_OK)
		return (ET_OK);
	destroy_function(comp->cur_func);
	return (comp->error.type);
}
