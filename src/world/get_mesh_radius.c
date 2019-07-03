/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mesh_radius.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:19:56 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/03 14:36:11 by mfischer         ###   ########.fr       */
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
	int		i;

	vec3_clear(res);
	i = -1;
	while (++i < mesh->polygonnum)
	{
		is_further(mesh->polygons[i].v01, res);
		is_further(mesh->polygons[i].v12, res);
		is_further(mesh->polygons[i].v20, res);
	}
	return (vec3_magnitude(res));
}
