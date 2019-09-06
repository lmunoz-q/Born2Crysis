/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_add_physics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:05:24 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/01 17:01:01 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	mesh_add_physics(t_mesh *mesh, double friction)
{
	int			i;
	t_polygon	tmp;

	if (!(mesh->walls = (t_wall *)malloc(sizeof(t_wall) * mesh->polygonnum)))
		return ;
	mesh->nb_walls = mesh->polygonnum;
	i = -1;
	while (++i < mesh->nb_walls)
	{
		tmp = mesh->polygons[i];
		mesh->walls[i] = polygon_to_wall(tmp, mesh->matrix);
		mesh->walls[i].friction = (friction == (double)-1) ? 0.05 : friction;
		mesh->walls[i].parent_mesh = mesh;
		if (vec3_dot(mesh->walls[i].normal, (t_vec3d){{0, 1, 0}}) < 0.5
				&& friction == (double)-1)
			mesh->walls[i].friction = 1;
		else if (friction == (double)-1)
			mesh->walls[i].friction = 0.90;
	}
}
