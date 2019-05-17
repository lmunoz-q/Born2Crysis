/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3dclipper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 22:56:59 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/18 00:14:33 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void edge_to_polygon(t_edge *e, t_polygon *p, int i)
{
	p->v_light[i] = e->l[0];
	if (i == 0)
	{
		vec4_copy(p->v01, e->p);
		p->v01_uv[0] = e->uv[0];
		p->v01_uv[1] = e->uv[1];
	}
	if (i == 1)
	{
		vec4_copy(p->v12, e->p);
		p->v12_uv[0] = e->uv[0];
		p->v12_uv[1] = e->uv[1];
	}
	if (i == 2)
	{
		vec4_copy(p->v20, e->p);
		p->v20_uv[0] = e->uv[0];
		p->v20_uv[1] = e->uv[1];
	}
}

static void		clip_2o1i(t_stack *outside, t_stack *inside)
{
	double	ratio;

	ratio = (ZNEAR - (((t_edge *)outside->data[0])->p[2]))
	/ (((t_edge *)inside->data[0])->p[2] - ((t_edge *)outside->data[0])->p[2]);
	((t_edge *)outside->data[0])->p[0] += (((t_edge *)inside->data[0])->p[0] - ((t_edge *)outside->data[0])->p[0]) * ratio;
	((t_edge *)outside->data[0])->p[1] += (((t_edge *)inside->data[0])->p[1] - ((t_edge *)outside->data[0])->p[1]) * ratio;
	((t_edge *)outside->data[0])->p[2] += (((t_edge *)inside->data[0])->p[2] - ((t_edge *)outside->data[0])->p[2]) * ratio;
	((t_edge *)outside->data[0])->uv[0] += (((t_edge *)inside->data[0])->uv[0] - ((t_edge *)outside->data[0])->uv[0]) * ratio;
	((t_edge *)outside->data[0])->uv[1] += (((t_edge *)inside->data[0])->uv[1] - ((t_edge *)outside->data[0])->uv[1]) * ratio;
	((t_edge *)outside->data[0])->l[0] += (((t_edge *)inside->data[0])->l[0] - ((t_edge *)outside->data[0])->l[0]) * ratio;
	ratio = (ZNEAR - (((t_edge *)outside->data[1])->p[2]))
	/ (((t_edge *)inside->data[0])->p[2] - ((t_edge *)outside->data[1])->p[2]);
	((t_edge *)outside->data[1])->p[0] += (((t_edge *)inside->data[0])->p[0] - ((t_edge *)outside->data[1])->p[0]) * ratio;
	((t_edge *)outside->data[1])->p[1] += (((t_edge *)inside->data[0])->p[1] - ((t_edge *)outside->data[1])->p[1]) * ratio;
	((t_edge *)outside->data[1])->p[2] += (((t_edge *)inside->data[0])->p[2] - ((t_edge *)outside->data[1])->p[2]) * ratio;
	((t_edge *)outside->data[1])->uv[0] += (((t_edge *)inside->data[0])->uv[0] - ((t_edge *)outside->data[1])->uv[0]) * ratio;
	((t_edge *)outside->data[1])->uv[1] += (((t_edge *)inside->data[0])->uv[1] - ((t_edge *)outside->data[1])->uv[1]) * ratio;
	((t_edge *)outside->data[1])->l[0] += (((t_edge *)inside->data[0])->l[0] - ((t_edge *)outside->data[1])->l[0]) * ratio;
}

static void		clip_1o2i(t_stack *outside, t_stack *inside, t_polygonlist *l, t_polygon *p)
{
	double		ratio;
	double		ratio2;
	t_polygon	*new;

	if (!(new = polygon_copy(p)))
		return ;
	ratio = (ZNEAR - (((t_edge *)outside->data[0])->p[2]))
	/ (((t_edge *)inside->data[0])->p[2] - ((t_edge *)outside->data[0])->p[2]);
	ratio2 = (ZNEAR - (((t_edge *)outside->data[0])->p[2]))
	/ (((t_edge *)inside->data[1])->p[2] - ((t_edge *)outside->data[0])->p[2]);
	new->v01[0] = ((t_edge *)outside->data[0])->p[0] + (((t_edge *)inside->data[0])->p[0] - ((t_edge *)outside->data[0])->p[0]) * ratio;
	new->v01[1] = ((t_edge *)outside->data[0])->p[1] + (((t_edge *)inside->data[0])->p[1] - ((t_edge *)outside->data[0])->p[1]) * ratio;
	new->v01[2] = ((t_edge *)outside->data[0])->p[2] + (((t_edge *)inside->data[0])->p[2] - ((t_edge *)outside->data[0])->p[2]) * ratio;
	new->v01_uv[0] = ((t_edge *)outside->data[0])->uv[0] + (((t_edge *)inside->data[0])->uv[0] - ((t_edge *)outside->data[0])->uv[0]) * ratio;
	new->v01_uv[1] = ((t_edge *)outside->data[0])->uv[1] + (((t_edge *)inside->data[0])->uv[1] - ((t_edge *)outside->data[0])->uv[1]) * ratio;
	new->v_light[0] = ((t_edge *)outside->data[0])->l[0] + (((t_edge *)inside->data[0])->l[0] - ((t_edge *)outside->data[0])->l[0]) * ratio;
	new->v12[0] = ((t_edge *)outside->data[0])->p[0] + (((t_edge *)inside->data[1])->p[0] - ((t_edge *)outside->data[0])->p[0]) * ratio2;
	new->v12[1] = ((t_edge *)outside->data[0])->p[1] + (((t_edge *)inside->data[1])->p[1] - ((t_edge *)outside->data[0])->p[1]) * ratio2;
	new->v12[2] = ((t_edge *)outside->data[0])->p[2] + (((t_edge *)inside->data[1])->p[2] - ((t_edge *)outside->data[0])->p[2]) * ratio2;
	new->v12_uv[0] = ((t_edge *)outside->data[0])->uv[0] + (((t_edge *)inside->data[1])->uv[0] - ((t_edge *)outside->data[0])->uv[0]) * ratio2;
	new->v12_uv[1] = ((t_edge *)outside->data[0])->uv[1] + (((t_edge *)inside->data[1])->uv[1] - ((t_edge *)outside->data[0])->uv[1]) * ratio2;
	new->v_light[1] = ((t_edge *)outside->data[0])->l[0] + (((t_edge *)inside->data[1])->l[0] - ((t_edge *)outside->data[0])->l[0]) * ratio2;
	new->is_clipped = TRUE;
	edge_to_polygon(inside->data[0], new, 2);
	list2_push(l, new);
	((t_edge *)outside->data[0])->p[0] += (((t_edge *)inside->data[1])->p[0] - ((t_edge *)outside->data[0])->p[0]) * ratio2;
	((t_edge *)outside->data[0])->p[1] += (((t_edge *)inside->data[1])->p[1] - ((t_edge *)outside->data[0])->p[1]) * ratio2;
	((t_edge *)outside->data[0])->p[2] += (((t_edge *)inside->data[1])->p[2] - ((t_edge *)outside->data[0])->p[2]) * ratio2;
	((t_edge *)outside->data[0])->uv[0] += (((t_edge *)inside->data[1])->uv[0] - ((t_edge *)outside->data[0])->uv[0]) * ratio2;
	((t_edge *)outside->data[0])->uv[1] += (((t_edge *)inside->data[1])->uv[1] - ((t_edge *)outside->data[0])->uv[1]) * ratio2;
	((t_edge *)outside->data[0])->l[0] += (((t_edge *)inside->data[1])->l[0] - ((t_edge *)outside->data[0])->l[0]) * ratio2;
}

static void		clip_znear_polygon(t_polygon *p, t_polygonlist *l)
{
	t_edge	edge[3];
	t_stack *inside;
	t_stack *outside;

	init_edge(p, edge);
	inside = stack_create(3);
	outside = stack_create(3);
	stack_push((p->v01[2] < ZNEAR) ? outside : inside, &edge[0]);
	stack_push((p->v12[2] < ZNEAR) ? outside : inside, &edge[1]);
	stack_push((p->v20[2] < ZNEAR) ? outside : inside, &edge[2]);
	if (outside->top == 2)
		p->active = FALSE;
	if (outside->top == 1)
		clip_2o1i(outside, inside);
	if (outside->top == 0)
		clip_1o2i(outside, inside, l, p);
	stack_destroy(&inside);
	stack_destroy(&outside);
}

void		clip_znear(t_polygonlist *l)
{
	t_node		*head;
	t_polygon	*p;

	head = l->list;
	while (head)
	{
		p = head->data;
		if (!p->active)
		{
			head = head->next;
			continue ;
		}
		clip_znear_polygon(p, l);
		head = head->next;
	}
}