/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mesh_radius.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:19:56 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/27 18:15:53 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

static void		is_further(t_vec3d d, t_vec3d *c)
{
	int i;

	i = -1;
	while (++i < 3)
		if (fabs(d.a[i]) > fabs(c->a[i]))
			c->a[i] = fabs(d.a[i]);
}

double			get_mesh_radius(t_mesh *mesh)
{
	t_vec3d	res;
	// t_vec4d	v01;
	// t_vec4d	v12;
	// t_vec4d	v20;
	int		i;

	vec3_clear(&res);
	i = -1;
	while (++i < mesh->polygonnum)
	{
		mesh->polygons[i].v01.a[3] = 0;
		mesh->polygons[i].v12.a[3] = 0;
		mesh->polygons[i].v20.a[3] = 0;
		// v01 = mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v01);
		// v12 = mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v12);
		// v20 = mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v20);
		is_further(mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v01).vec3d, &res);
		is_further(mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v12).vec3d, &res);
		is_further(mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v20).vec3d, &res);
		mesh->polygons[i].v01.a[3] = 1;
		mesh->polygons[i].v12.a[3] = 1;
		mesh->polygons[i].v20.a[3] = 1;
	}
	return (vec3_magnitude(res));
}
