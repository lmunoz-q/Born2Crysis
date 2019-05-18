/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dclipper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:27:23 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/18 16:22:18 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static t_bool   is_right(double  p1[2], double p2[2], double c[2])
{
	t_bool res;

	res = (((p2[0] - p1[0]) * (c[1] - p1[1]) -
        (p2[1] - p1[1]) * (c[0] - p1[0])) > 0);
	return (res);
}

t_bool	is_all_inside(t_polygon *p, t_vec2i win_size)
{
	t_bool res;

	res = TRUE;
	if (p->v01[0] < -1 || p->v01[0] >= win_size.x + 1 || p->v01[1] < -1 || p->v01[1] >= win_size.y + 1)
		res = FALSE;
	if (p->v12[0] < -1 || p->v12[0] >= win_size.x + 1 || p->v12[1] < -1 || p->v12[1] >= win_size.y + 1)
		res = FALSE;
	if (p->v20[0] < -1 || p->v20[0] >= win_size.x + 1 || p->v20[1] < -1 || p->v20[1] >= win_size.y + 1)
		res = FALSE;
	return (res);
}

static t_vec2d     	line_intersect_2d(double a1[2], double a2[2], double b1[2], double b2[2])
{
    t_vec3d     p[2];
    t_vec2d     res;
    double      delta;

    p[0].y = a2[1] - a1[1];
    p[0].x = a1[0] - a2[0];
    p[0].z = p[0].y*a1[0] + p[0].x*a1[1];
    p[1].y = b2[1] - b1[1];
    p[1].x = b1[0] - b2[0];
    p[1].z = p[1].y*b1[0] + p[1].x*b1[1];
    delta = p[0].y*p[1].x - p[1].y*p[0].x;
    res.x = ((p[1].x*p[0].z) - (p[0].x*p[1].z))/delta;
    res.y = ((p[0].y*p[1].z) - (p[1].y*p[0].z))/delta;
    return (res);
}

static double	get_intersection_ratio(double a1[2], double a2[2], double b1[2], double b2[2])
{
	t_vec2d p;
	double	tmp[2];
	double	tmp2[2];
	double	res;

	p = line_intersect_2d(a1, a2, b1, b2);
	vec2vec2_substract(a2, a1, tmp);
	tmp2[0] = p.x - a1[0];
	tmp2[1] = p.y - a1[1];
	res = vec2_magnitude(tmp2) / vec2_magnitude(tmp);
	return (res);
}

static void	clip_2o1i(t_stack *outside, t_stack *inside, double edge[2][2])
{
	double ratio;
	
	ratio = get_intersection_ratio(((t_edge *)outside->data[0])->p, ((t_edge *)inside->data[0])->p, edge[0], edge[1]);
	((t_edge *)outside->data[0])->p[0] += (((t_edge *)inside->data[0])->p[0] - ((t_edge *)outside->data[0])->p[0]) * ratio;
	((t_edge *)outside->data[0])->p[1] += (((t_edge *)inside->data[0])->p[1] - ((t_edge *)outside->data[0])->p[1]) * ratio;
	((t_edge *)outside->data[0])->p[2] += (((t_edge *)inside->data[0])->p[2] - ((t_edge *)outside->data[0])->p[2]) * ratio;
	((t_edge *)outside->data[0])->uv[0] += (((t_edge *)inside->data[0])->uv[0] - ((t_edge *)outside->data[0])->uv[0]) * ratio;
	((t_edge *)outside->data[0])->uv[1] += (((t_edge *)inside->data[0])->uv[1] - ((t_edge *)outside->data[0])->uv[1]) * ratio;
	((t_edge *)outside->data[0])->l[0] += (((t_edge *)inside->data[0])->l[0] - ((t_edge *)outside->data[0])->l[0]) * ratio;
	ratio = get_intersection_ratio(((t_edge *)outside->data[1])->p, ((t_edge *)inside->data[0])->p, edge[0], edge[1]);
	((t_edge *)outside->data[1])->p[0] += (((t_edge *)inside->data[0])->p[0] - ((t_edge *)outside->data[1])->p[0]) * ratio;
	((t_edge *)outside->data[1])->p[1] += (((t_edge *)inside->data[0])->p[1] - ((t_edge *)outside->data[1])->p[1]) * ratio;
	((t_edge *)outside->data[1])->p[2] += (((t_edge *)inside->data[0])->p[2] - ((t_edge *)outside->data[1])->p[2]) * ratio;
	((t_edge *)outside->data[1])->uv[0] += (((t_edge *)inside->data[0])->uv[0] - ((t_edge *)outside->data[1])->uv[0]) * ratio;
	((t_edge *)outside->data[1])->uv[1] += (((t_edge *)inside->data[0])->uv[1] - ((t_edge *)outside->data[1])->uv[1]) * ratio;
	((t_edge *)outside->data[1])->l[0] += (((t_edge *)inside->data[0])->l[0] - ((t_edge *)outside->data[1])->l[0]) * ratio;
}

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

void	clip_1o2i(t_stack *outside, t_stack *inside, double edge[2][2], t_polygonlist *l, t_polygon *p)
{
	double		ratio;
	double		ratio2;
	t_polygon	*new;

	if (!(new = polygon_copy(p)))
		return ;
	ratio = get_intersection_ratio(((t_edge *)outside->data[0])->p, ((t_edge *)inside->data[0])->p, edge[0], edge[1]);
	ratio2 = get_intersection_ratio(((t_edge *)outside->data[0])->p, ((t_edge *)inside->data[1])->p, edge[0], edge[1]);
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
	//list2_insert(l, head, new);
	list2_push(l, new);
	((t_edge *)outside->data[0])->p[0] += (((t_edge *)inside->data[1])->p[0] - ((t_edge *)outside->data[0])->p[0]) * ratio2;
	((t_edge *)outside->data[0])->p[1] += (((t_edge *)inside->data[1])->p[1] - ((t_edge *)outside->data[0])->p[1]) * ratio2;
	((t_edge *)outside->data[0])->p[2] += (((t_edge *)inside->data[1])->p[2] - ((t_edge *)outside->data[0])->p[2]) * ratio2;
	((t_edge *)outside->data[0])->uv[0] += (((t_edge *)inside->data[1])->uv[0] - ((t_edge *)outside->data[0])->uv[0]) * ratio2;
	((t_edge *)outside->data[0])->uv[1] += (((t_edge *)inside->data[1])->uv[1] - ((t_edge *)outside->data[0])->uv[1]) * ratio2;
	((t_edge *)outside->data[0])->l[0] += (((t_edge *)inside->data[1])->l[0] - ((t_edge *)outside->data[0])->l[0]) * ratio2;
}

void		clip_polygon(t_polygonlist *l, t_polygon *p, double edge[2][2])
{
	t_edge	point[3];
	t_stack *inside;
	t_stack *outside;
	(void)l;

	if (!p->active)
		return ;
	init_edge(p, point);
	inside = stack_create(3);
	outside = stack_create(3);
	stack_push((is_right(edge[0], edge[1], p->v01) ? inside : outside), &point[0]);
	stack_push((is_right(edge[0], edge[1], p->v12) ? inside : outside), &point[1]);
	stack_push((is_right(edge[0], edge[1], p->v20) ? inside : outside), &point[2]);
	if (outside->top == 2)
		p->active = FALSE;
	if (outside->top == 1)
		clip_2o1i(outside, inside, edge);
	if (outside->top == 0)
		clip_1o2i(outside, inside, edge, l, p);
	stack_destroy(&inside);
	stack_destroy(&outside);
}

void		clip_polygons_2d(t_polygonlist	*l, t_vec2i win_size)
{
	t_node		*head;
	t_polygon	*p;

	head = l->list;
	while (head)
	{
		p = head->data;
		clip_polygon(l, p, (double [2][2]){{0, win_size.y - 1}, {0, 0}});
		head = head->next;
	}
	head = l->list;
	while (head)
	{
		p = head->data;
		clip_polygon(l, p, (double [2][2]){{0,0}, {win_size.x - 1, 0}});
		head = head->next;
	}
	head = l->list;
	while (head)
	{
		p = head->data;
		clip_polygon(l, p, (double [2][2]){{win_size.x - 1, 0}, {win_size.x - 1, win_size.y - 1}});
		head = head->next;
	}
	head = l->list;
	while (head)
	{
		p = head->data;
		clip_polygon(l, p, (double [2][2]){{win_size.x - 1, win_size.y - 1}, {0, win_size.y - 1}});
		head = head->next;
	}
}
