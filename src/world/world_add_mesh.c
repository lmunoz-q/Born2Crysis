/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_add_mesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:50:44 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/19 11:11:33 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void		world_add_mesh(t_mesh *mesh, t_world *world, int sector_id)
{
	t_sector	*sector;
	t_mesh		*mesh_tmp;

	if (!(sector = get_sector(sector_id, world)))
		return ;
	if (!(mesh_tmp = (t_mesh *)malloc(sizeof(t_mesh) * (sector->meshnum + 1))))
		return ;
	mf_memcpy(mesh_tmp, sector->mesh, sizeof(t_mesh) * sector->meshnum);
	mf_memcpy(&mesh_tmp[sector->meshnum], mesh, sizeof(t_mesh));
	if (sector->mesh)
		free(sector->mesh);
	sector->meshnum++;
	sector->mesh = mesh_tmp;
}