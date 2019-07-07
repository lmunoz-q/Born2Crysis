/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_portal_outline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:42:45 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/07 16:46:10 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

static void		fill_buffer(double **buff, t_polygon *p, int n)
{
	int			i;
	int			j;

	i = -1;
	j = -1;
	while (++i < n)
	{
		buff[++j][0] = p[i].v01[0];
		buff[j][1] = p[i].v01[1];
		buff[j][2] = p[i].v01[2];
		buff[++j][0] = p[i].v12[0];
		buff[j][1] = p[i].v12[1];
		buff[j][2] = p[i].v12[2];
		buff[++j][0] = p[i].v20[0];
		buff[j][1] = p[i].v20[1];
		buff[j][2] = p[i].v20[2];
	}
}

static t_bool		sort_by_y(void *f, void *s)
{
	if (((double *)f)[1] <= ((double *)s)[1])
		return (TRUE);
	return (FALSE);
}

static t_bool		sort_by_n(void *f, void *s)
{
	if (((double *)f)[3] >= ((double *)s)[3])
		return (TRUE);
	return (FALSE);
}

static void		compute_angles(double **buff, int nb, double normal[3])
{
	int		i;
	double	ref[3];
	double	tmp[3];

	vec3vec3_substract(buff[1], buff[0], tmp);
	vec3vec3_crossproduct(tmp, normal, ref);
	vec3_normalize_s(ref);
	i = 0;
	while (++i < nb)
	{
		vec3vec3_substract(buff[i], buff[0], tmp);
		vec3_normalize_s(tmp);
		buff[i][3] = vec3_dot(ref, tmp);
	}
}

static t_bool		is_clock_wise(double a[3], double b[3], double c[3], double n[3])
{
	double	t1[3];
	double	t2[3];
	double	cross[3];

	vec3vec3_substract(b, a, t1);
	vec3vec3_substract(c, a, t2);
	vec3vec3_crossproduct(t1, t2, cross);
	vec3_normalize_s(cross);
	if (vec3_dot(cross, n) < 0)
		return (FALSE);
	return (TRUE);
}

static void		gen_outbound(double **buffer, int n, t_mesh *m)
{
	t_stack	*points;
	int		i;

	points = stack_create(n);
	i = -1;
	while (++i < n)
	{
		while (points->top > 1 && !is_clock_wise(stack_next_to_top(points), stack_top(points), buffer[i], m->portal_normal))
			stack_pop(points);
		stack_push(points, buffer[i]);
	}
	if (!(m->portal_outbound = (double **)malloc(sizeof(double *) * (points->top + 1))))
		return ;
	printf("%d\n", points->top);
	m->portal_outbound_count = points->top + 1;
	i = -1;
	while ((m->portal_outbound[++i] = stack_pop(points)));
	stack_destroy(&points);
}

void		gen_portal_outline(t_mesh *m)
{
	double		**buff;
	int			i;
	
	printf("BUILDING PORTAL\n");
	if (!(buff = (double **)malloc(sizeof(double *) * m->polygonnum * 3)))
		return ;
	i = -1;
	while (++i < m->polygonnum * 3)
		buff[i] = (double *)malloc(sizeof(double) * 4);
	fill_buffer(buff, m->polygons, m->polygonnum);
	mf_quicksort_c(buff, (int [2]){0, (m->polygonnum * 3) - 1},
					sort_by_y, sizeof(double *));
	compute_angles(buff, m->polygonnum * 3, m->portal_normal);
	mf_quicksort_c(buff, (int [2]){1, (m->polygonnum * 3) - 1},
					sort_by_n, sizeof(double *));
	gen_outbound(buff, m->polygonnum * 3, m);
	i = -1;
	while (++i < m->portal_outbound_count)
		printf("%f, %f, %f, %f\n", m->portal_outbound[i][0], m->portal_outbound[i][1], m->portal_outbound[i][2], m->portal_outbound[i][3]);

}