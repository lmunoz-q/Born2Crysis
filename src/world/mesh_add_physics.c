/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_add_physics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:05:24 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 19:48:06 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	mesh_add_physics(t_mesh *mesh)
{
	int			i;
	t_polygon	tmp;
	double		dot_tmp;

	if (!(mesh->walls = (t_wall *)malloc(sizeof(t_wall) * mesh->polygonnum)))
		return ;
	mesh->nb_walls = mesh->polygonnum;
	i = -1;
	while (++i < mesh->nb_walls)
	{
		tmp = mesh->polygons[i];
		mesh->walls[i] = polygon_to_wall(tmp, mesh->matrix);
		mesh->walls[i].friction = 0.05;
		mesh->walls[i].on_contact_trigger = EFF_NOTHING;
		if ((dot_tmp = vec3_dot(vec3_normalize(vec3p_get_normal(
			mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v01).c3.vec3d,
			mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v12).c3.vec3d,
			mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v20).c3.vec3d)),
				(t_vec3d){.a = {0, 1, 0}})) > GROUND_RATIO)
			mesh->walls[i].on_contact_trigger = EFF_RESET_JUMP;
		else if (dot_tmp < 0.5)
			mesh->walls[i].friction = 0.99;
		else
			mesh->walls[i].friction = 0.90;
	}
}
