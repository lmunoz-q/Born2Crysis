/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mesh_radius.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:19:56 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/11 19:32:37 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

static void		is_further(double d[3], double c[3])
{
	int i;

	i = -1;
	while (++i < 3)
		if (fabs(d[i]) > fabs(c[i]))
			c[i] = fabs(d[i]);
}

double			get_mesh_radius(t_mesh *mesh)
{
	double	res[3];
	double	v01[4];
	double	v12[4];
	double	v20[4];
	int		i;

	vec3_clear(res);
	i = -1;
	while (++i < mesh->polygonnum)
	{
		mesh->polygons[i].v01[3] = 0;
		mesh->polygons[i].v12[3] = 0;
		mesh->polygons[i].v20[3] = 0;
		mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v01, v01);
		mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v12, v12);
		mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v20, v20);
		is_further(v01, res);
		is_further(v12, res);
		is_further(v20, res);
		mesh->polygons[i].v01[3] = 1;
		mesh->polygons[i].v12[3] = 1;
		mesh->polygons[i].v20[3] = 1;
	}
	return (vec3_magnitude(res));
}
