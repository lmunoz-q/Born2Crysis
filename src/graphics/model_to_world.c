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

static t_bool	cull_backface(t_polygon *p, double pos[3])
{
	double tmp[3];
	double tmp2[3];
	
	vec3vec3_substract(p->v20, p->v01, tmp);
	vec3vec3_substract(p->v12, p->v01, tmp2);
	vec3vec3_crossproduct(tmp, tmp2, p->normal);
	vec3_normalize_s(p->normal);
	vec3vec3_substract(p->v01, pos, tmp);
	return ((vec3_dot(p->normal, tmp) > 0) ? TRUE : FALSE);
}

int			model_to_world(t_mesh *mesh, double pos[3], t_polygon *p)
{
	int			num;
	int			i;
	t_polygon	tmp;

	i = -1;
	num = 0;
	while (++i < mesh->polygonnum)
	{
		mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v01, tmp.v01);
		mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v12, tmp.v12);
		mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v20, tmp.v20);
		if (cull_backface(&tmp, pos))
		{
			vec2_copy(tmp.v01_uv, mesh->polygons[i].v01_uv);
			vec2_copy(tmp.v12_uv, mesh->polygons[i].v12_uv);
			vec2_copy(tmp.v20_uv, mesh->polygons[i].v20_uv);
			vec3_copy(tmp.v_light, (double [3]){0, 0, 0});
			
			tmp.tex_id = mesh->polygons[i].tex_id;
			tmp.transparency = mesh->polygons[i].transparency;
			p[num] = tmp;
			num++;
		}
	}
	return (num);
}
