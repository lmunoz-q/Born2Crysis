/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2p.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:59:43 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/13 19:30:08 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

inline static void	sub_func(double tmp1[4], double tmp2[4],
								double tmp3[4], t_polygon *p)
{
	p->v01[0] = tmp1[0] / tmp1[2];
	p->v12[0] = tmp2[0] / tmp2[2];
	p->v20[0] = tmp3[0] / tmp3[2];
	p->v01[1] = tmp1[1] / tmp1[2];
	p->v12[1] = tmp2[1] / tmp2[2];
	p->v20[1] = tmp3[1] / tmp3[2];
	p->v01[2] *= -1.0;
	p->v12[2] *= -1.0;
	p->v20[2] *= -1.0;
}

inline static void	sub_func_2(t_polygon *p, t_vec2i size)
{
	p->v01[0] = (p->v01[0] + 1.0) * (double)(size.x / 2.0);
	p->v12[0] = (p->v12[0] + 1.0) * (double)(size.x / 2.0);
	p->v20[0] = (p->v20[0] + 1.0) * (double)(size.x / 2.0);
	p->v01[1] = (p->v01[1] + 1.0) * (double)(size.y / 2.0);
	p->v12[1] = (p->v12[1] + 1.0) * (double)(size.y / 2.0);
	p->v20[1] = (p->v20[1] + 1.0) * (double)(size.y / 2.0);
}

void				view_to_projection(t_polygonlist *l,
								double mat[4][4], t_vec2i size)
{
	t_node		*head;
	t_polygon	*p;
	double		tmp1[4];
	double		tmp2[4];
	double		tmp3[4];

	head = l->list;
	while (head)
	{
		p = head->data;
		if (!p->active)
		{
			head = head->next;
			continue ;
		}
		//printf("%f, %f, %f\n", p->v20[0], p->v20[1], p->v20[2]);
		mat4vec4_multiply(mat, p->v01, tmp1);
		mat4vec4_multiply(mat, p->v12, tmp2);
		mat4vec4_multiply(mat, p->v20, tmp3);
		//printf("%f, %f, %f\n", tmp1[0], tmp1[1], tmp1[2]);
		sub_func(tmp1, tmp2, tmp3, p);
		sub_func_2(p, size);
		head = head->next;
	}
}
