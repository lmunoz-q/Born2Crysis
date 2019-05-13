/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m2w.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:02:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/13 20:27:05 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "graphics.h"

void		model_to_world(t_polygonlist *v, double matrix[4][4])
{
	t_node		*head;
	t_polygon	*tmp;

	head = v->list;
	while (head)
	{
		tmp = head->data;
		mat4vec4_multiply(matrix, tmp->v01_o, tmp->v01);
		mat4vec4_multiply(matrix, tmp->v12_o, tmp->v12);
		mat4vec4_multiply(matrix, tmp->v20_o, tmp->v20);
		mat4vec4_multiply(matrix, tmp->normal_o, tmp->normal);
		vec2scalar_add(tmp->v01_uv_o, 0, tmp->v01_uv);
		vec2scalar_add(tmp->v12_uv_o, 0, tmp->v12_uv);
		vec2scalar_add(tmp->v20_uv_o, 0, tmp->v20_uv);
		head = head->next;
	}
}
