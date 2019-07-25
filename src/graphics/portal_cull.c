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

t_bool		is_inside_plane(t_vec3d p, t_vec3d n, t_vec3d m, double rad)
{
	if (vec3_dot(vec3vec3_substract(p, m), n) > 0)
		return (TRUE);
	if (fabs(dist_pointplane(n, p, m)) < rad)
		return (TRUE);
	return (FALSE);
}

void		cull_against_portal_polygon(t_mesh *m, int mn, t_polygon *p, t_vec4d c)
{
	int			i;
	t_vec4d		pp;
	t_vec3d		n;
	t_bool		res;
	
	res = TRUE;
	i = -1;
	while (++i < mn)
	{
		n = vec3p_get_normal(c.vec3d, p->v01.vec3d, p->v12.vec3d);
		vec4_init(&pp);
		pp = mat4vec4_multiply(m[i].matrix, pp);
		if (!is_inside_plane(p->v01.vec3d, n, pp.vec3d, m[i].radius))
			res = FALSE;
		n = vec3p_get_normal(c.vec3d, p->v12.vec3d, p->v20.vec3d);
		vec4_init(&pp);
		pp = mat4vec4_multiply(m[i].matrix, pp);
		if (!is_inside_plane(p->v12.vec3d, n, pp.vec3d, m[i].radius))
			res = FALSE;
		n = vec3p_get_normal(c.vec3d, p->v20.vec3d, p->v01.vec3d);
		vec4_init(&pp);
		pp = mat4vec4_multiply(m[i].matrix, pp);
		if (!is_inside_plane(p->v20.vec3d, n, pp.vec3d, m[i].radius))
			res = FALSE;
		if (res)
			m[i].active = TRUE;
	}
}

void		portal_cull(t_mesh *m, int mn, t_mesh *portal, t_vec4d cam_pos)
{
	int		i;
	t_polygon	tmp;

	activate_meshes(m, mn);
	i = -1;
	while (++i < portal->polygonnum)
	{
		tmp.v01 = mat4vec4_multiply(portal->matrix, portal->polygons[i].v01);
		tmp.v12 = mat4vec4_multiply(portal->matrix, portal->polygons[i].v12);
		tmp.v20 = mat4vec4_multiply(portal->matrix, portal->polygons[i].v20);
		cull_against_portal_polygon(m, mn, &tmp, cam_pos);
	}
}
