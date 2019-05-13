/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w2v.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:42:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/13 19:32:32 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		world_to_view(t_polygonlist *v, double view_matrix[4][4])
{
	t_polygon	*p;
	t_node		*head;
    double		tmp[4];

    head = v->list;
    while (head)
    {
		p = head->data;
		if (!p->active)
		{
			head = head->next;
			continue ;
		}
        mat4vec4_multiply(view_matrix, p->v01, tmp);
        vec4_copy(p->v01, tmp);
        mat4vec4_multiply(view_matrix, p->v12, tmp);
        vec4_copy(p->v12, tmp);
        mat4vec4_multiply(view_matrix, p->v20, tmp);
        vec4_copy(p->v20, tmp);
		head = head->next;
    }
}
