/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backface_culler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:18:42 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/11 00:09:12 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "graphics.h"

void		cull_backfaces(t_polygonlist *v, double mouse_pos[3])
{
	t_node		*head;
	t_polygon	*p;
    double		tmp[3];
    double		tmp2[3];

	head = v->list;
    while (head)
    {
		p = head->data;
		if (!p->preloaded_normal)
		{
        	vec3vec3_substract(p->v20, p->v01, tmp);
        	vec3vec3_substract(p->v12, p->v01, tmp2);
        	vec3vec3_crossproduct(tmp, tmp2, p->normal);
        	vec3_normalize_s(p->normal);
		}
		vec3vec3_substract(p->v01, mouse_pos, tmp);
		p->active = (vec3_dot(p->normal, tmp) > 0) ? TRUE : FALSE;
	   head = head->next;
    }
}
