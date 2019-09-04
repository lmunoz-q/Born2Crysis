/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:38:20 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:38:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmml_functions.h>

t_op_param	*eval_params(t_compiler *comp, int nb_param)
{
	int					it[2];
	char				s;
	static t_op_param	p[4];

	it[1] = 0;
	while (comp->error.type == ET_OK && *comp->head != '\0')
	{
		while (*comp->head == ' ' || *comp->head == '\t')
			++comp->head;
		if (*comp->head == '\0' || it[1] >= nb_param)
			break ;
		it[0] = 0;
		while (comp->head[it[0]] != ' ' && comp->head[it[0]] != '\t'
				&& comp->head[it[0]] != '\0')
			++it[0];
		s = comp->head[it[0]];
		comp->head[it[0]] = '\0';
		p[it[1]++] = eval_param(comp);
		comp->head[it[0]] = s;
		comp->head = &comp->head[it[0] + (s != '\0')];
	}
	if (comp->error.type == ET_OK && (it[1] != nb_param || *comp->head != '\0'))
		set_error(comp, (it[1] > nb_param || *comp->head != '\0')
						? ET_TOO_MANY_PARAMETERS : ET_TOO_FEW_PARAMETERS);
	return (p);
}
