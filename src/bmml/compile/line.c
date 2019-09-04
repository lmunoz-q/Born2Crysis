/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:38:30 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:38:32 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_compiler	*compile_line(t_compiler *comp)
{
	t_op_table	*ot;
	int			it;
	char		s;

	it = 0;
	while (comp->head[it] != ' ' && comp->head[it] != '\t'
			&& comp->head[it] != '\0')
		++it;
	if (comp->head[it] == '\0')
		return (set_error(comp, ET_TOO_FEW_PARAMETERS));
	s = comp->head[it];
	comp->head[it] = '\0';
	if ((ot = get_op(comp->head, 0)) == NULL)
		return (set_error(comp, ET_INVALID_INSTRUCTION));
	comp->head[it] = s;
	comp->head += it;
	while (*comp->head == ' ' || *comp->head == '\t')
		++comp->head;
	if (*comp->head == '\0')
		set_error(comp, ET_TOO_FEW_PARAMETERS);
	else
		ot->compile(ot->code, comp);
	return (comp);
}
