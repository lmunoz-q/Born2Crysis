/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_to_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 22:37:58 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/09 13:10:27 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static t_bool	cull_backface(t_polygon *p, t_vec4d pos)
{
	p->normal = vec3_normalize(vec3vec3_crossproduct(vec3vec3_substract(
		p->v20.c3.vec3d, p->v01.c3.vec3d), vec3vec3_substract(p->v12.c3.vec3d,
			p->v01.c3.vec3d)));
	return ((vec3_dot(p->normal, vec3vec3_substract(p->v01.c3.vec3d,
		pos.c3.vec3d)) > 0) ? TRUE : FALSE);
}

int			model_to_world(t_mesh *mesh, t_vec4d pos, t_polygon *p)
{
	int			num;
	int			i;
	t_polygon	tmp;

	i = -1;
	num = 0;
	while (++i < mesh->polygonnum)
	{
		tmp.v01 = mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v01);
		tmp.v12 = mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v12);
		tmp.v20 = mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v20);
		if (cull_backface(&tmp, pos))
		{
			tmp.v01_uv = mesh->polygons[i].v01_uv;
			tmp.v12_uv = mesh->polygons[i].v12_uv;
			tmp.v20_uv = mesh->polygons[i].v20_uv;
			tmp.v_light = (t_vec3d){.a = {0, 0, 0}};
			tmp.tex_id = mesh->polygons[i].tex_id;
			tmp.transparency = mesh->polygons[i].transparency;
			p[num] = tmp;
			num++;
		}
	}
	return (num);
}
