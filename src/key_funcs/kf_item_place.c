/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_item_place.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:49:19 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 16:52:25 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void		kf_item_place(void *param)
{
	t_e			*e;
	t_mesh		*mesh;
	int			i;

	e = param;
	if (e->editor.is_in_view)
	{
		mesh = mesh_copy(e->editor.item_placer);
		if (e->editor.is_making_portail)
			mesh->sector_id = e->editor.secteur2_courant;
		world_add_mesh(mesh, &e->world, e->editor.secteur_courant);
		mesh = mesh_copy(e->editor.item_placer);
		if (e->editor.is_making_portail)
		{
			i = -1;
			while ((Uint32)++i < mesh->polygonnum)
			{
				mf_swap_doubles(mesh->polygons[i].v01.a, mesh->polygons[i].v12.a, 3);
				mf_swap_doubles(mesh->polygons[i].v01_uv.a, mesh->polygons[i].v12_uv.a, 2);
			}
			mesh->sector_id = e->editor.secteur_courant;
			world_add_mesh(mesh, &e->world, e->editor.secteur2_courant);
		}
	}
}