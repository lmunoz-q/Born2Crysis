/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_add_physics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:05:24 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/25 17:44:04 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	mesh_add_physics(t_mesh *mesh)
{
	int			i;
	t_polygon	tmp;

	if (!(mesh->walls = (t_wall *)malloc(sizeof(t_wall) * mesh->polygonnum)))
		return ;
	mesh->nb_walls = mesh->polygonnum;
	i = -1;
	while ((Uint32)++i < mesh->nb_walls)
	{
		tmp = mesh->polygons[i];
		mesh->walls[i] = polygon_to_wall(tmp, mesh->matrix);
		mesh->walls[i].friction = 0.4;
		mesh->walls[i].on_contact_trigger = EFF_RESET_JUMP;
	}
}