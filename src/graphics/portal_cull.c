/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_cull.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 21:26:23 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/08 00:17:27 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		activate_meshes(t_mesh *m, int mn)
{
	int i;

	i = -1;
	while (++i < mn)
		m[i].active = FALSE;
}

t_bool		is_inside_plane(double p[3], double n[3], double m[3], double rad)
{
	double	tmp[3];

	vec3vec3_substract(p, m, tmp);
	if (vec3_dot(tmp, n) > 0)
		return (TRUE);
	if (fabs(dist_pointplane(n, p, m)) < rad)
		return (TRUE);
	return (FALSE);
}

void		cull_against_portal_polygon(t_mesh *m, int mn, t_polygon *p, double c[4])
{
	int			i;
	double		pp[4];
	double		n[4];
	t_bool		res;
	
	res = TRUE;
	i = -1;
	while (++i < mn)
	{
		vec3p_get_normal(c, p->v01, p->v12, n);
		vec4_init(pp);
		mat4vec4_multiply(m[i].matrix, pp, pp);
		if (!is_inside_plane(p->v01, n, pp, m[i].radius))
			res = FALSE;
		vec3p_get_normal(c, p->v12, p->v20, n);
		vec4_init(pp);
		mat4vec4_multiply(m[i].matrix, pp, pp);
		if (!is_inside_plane(p->v12, n, pp, m[i].radius))
			res = FALSE;
		vec3p_get_normal(c, p->v20, p->v01, n);
		vec4_init(pp);
		mat4vec4_multiply(m[i].matrix, pp, pp);
		if (!is_inside_plane(p->v20, n, pp, m[i].radius))
			res = FALSE;
		if (res)
			m[i].active = TRUE;
	}
}

void		portal_cull(t_mesh *m, int mn, t_mesh *portal, double cam_pos[4])
{
	int		i;
	t_polygon	tmp;

	activate_meshes(m, mn);
	i = -1;
	while (++i < portal->polygonnum)
	{
		mat4vec4_multiply(portal->matrix, portal->polygons[i].v01, tmp.v01);
		mat4vec4_multiply(portal->matrix, portal->polygons[i].v12, tmp.v12);
		mat4vec4_multiply(portal->matrix, portal->polygons[i].v20, tmp.v20);
		cull_against_portal_polygon(m, mn, &tmp, cam_pos);
	}
}