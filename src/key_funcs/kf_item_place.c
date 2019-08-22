/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_item_place.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:49:19 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 14:20:41 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

static void	make_portal(t_e	*e, t_mesh *mesh)
{
	int			i;

	i = -1;
	while (++i < mesh->polygonnum)
	{
		mf_swap_doubles(mesh->polygons[i].v01.a, mesh->polygons[i].v12.a, 3);
		mf_swap_doubles(mesh->polygons[i].v01_uv.a, mesh->polygons[i].v12_uv.a, 2);
	}
	mesh->sector_id = e->editor.secteur_courant;
	world_add_mesh(mesh, &e->world, e->editor.secteur2_courant);
}

static void	make_light(t_e *e, t_mesh *mesh)
{
	t_light		light;
	t_sector	*tmp;

	light.pos_o = (t_vec4d){.a = {0, 0, 0, 0}};
	light.mat = mesh->matrix;
	light.dir = (t_vec3d){.a = {1, 0, 0}};
	light.fallof = e->editor.lux_fallof;
	light.intensity = e->editor.lux_intensity;
	light.type = e->editor.lux_type;
	tmp = get_sector( e->editor.secteur_courant, &e->world);
	if (tmp)
		light_add(&tmp->lights, light);
}

void		kf_item_place(void *param)
{
	t_e			*e;
	t_mesh		*mesh;
	

	e = param;
	if (e->editor.is_in_view)
	{
		if (e->editor.is_making_portail && e->editor.secteur_courant == e->editor.secteur2_courant)
			return ;
		mesh = mesh_copy(e->editor.item_placer);
		if (e->editor.is_making_portail)
			mesh->sector_id = e->editor.secteur2_courant;
		world_add_mesh(mesh, &e->world, e->editor.secteur_courant);
		mesh = mesh_copy(e->editor.item_placer);
		if (e->editor.is_making_portail)
			make_portal(e, mesh);
		if (e->editor.is_light)
			make_light(e, mesh);
	}
}