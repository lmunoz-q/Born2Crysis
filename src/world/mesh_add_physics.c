/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_add_physics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:05:24 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/28 12:26:22 by mfischer         ###   ########.fr       */
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
	while ((Uint32)++i < mesh->nb_walls)
	{
		tmp = mesh->polygons[i];
		mesh->walls[i] = polygon_to_wall(tmp, mesh->matrix);
		mesh->walls[i].friction = 0.05;
		mesh->walls[i].on_contact_trigger = EFF_NOTHING;
		if ((dot_tmp = vec3_dot(vec3_normalize(vec3p_get_normal(mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v01).c3.vec3d,
													mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v12).c3.vec3d,
													mat4vec4_multiply(mesh->matrix, mesh->polygons[i].v20).c3.vec3d)), (t_vec3d){.a = {0, 1, 0}})) > GROUND_RATIO)
			mesh->walls[i].on_contact_trigger = EFF_RESET_JUMP;
		else if (dot_tmp < 0.5)
			mesh->walls[i].friction = 0.99;
		else
			mesh->walls[i].friction = 0.90;
		printf("normal: %f %f %f\n", mesh->walls[i].normal.n.x, mesh->walls[i].normal.n.y, mesh->walls[i].normal.n.z);
		printf("center: %f %f %f\n", mesh->walls[i].center.n.x, mesh->walls[i].center.n.y, mesh->walls[i].center.n.z);
		printf("v01: %f %f %f\n", mesh->walls[i].vertices[0].n.x, mesh->walls[i].vertices[0].n.y, mesh->walls[i].vertices[0].n.z);
		printf("v12: %f %f %f\n", mesh->walls[i].vertices[1].n.x, mesh->walls[i].vertices[1].n.y, mesh->walls[i].vertices[1].n.z);
		printf("v20: %f %f %f\n", mesh->walls[i].vertices[2].n.x, mesh->walls[i].vertices[2].n.y, mesh->walls[i].vertices[2].n.z);
		printf("friction: %f\n", mesh->walls[i].friction);
		printf("radius: %f\n", mesh->walls[i].radius);
	}
}