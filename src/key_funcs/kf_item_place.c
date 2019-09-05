/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_item_place.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:49:19 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/05 16:54:32 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

static void	make_portal(t_e *e)
{
	int			i;
	t_mesh		*mesh;

	if (!(mesh = mesh_copy(e->editor.item_placer)))
		return ;
	i = -1;
	while (++i < mesh->polygonnum)
	{
		mf_swap_doubles(mesh->polygons[i].v01.a, mesh->polygons[i].v12.a, 3);
		mf_swap_doubles(mesh->polygons[i].v01_uv.a,
			mesh->polygons[i].v12_uv.a, 2);
	}
	mesh->sector_id = e->editor.secteur_courant;
	world_add_mesh(mesh, &e->world, e->editor.secteur2_courant);
	free(mesh);
}

static void	make_light(t_e *e, t_mesh *mesh)
{
	t_light		light;
	t_sector	*tmp;

	light.pos_o = (t_vec4d){.a = {0, 0, 0, 1}};
	light.mat = mesh->matrix;
	light.dir = (t_vec3d){.a = {1, 0, 0}};
	light.fallof = e->editor.lux_fallof;
	light.intensity = e->editor.lux_intensity;
	light.type = e->editor.lux_type;
	tmp = get_sector(e->editor.secteur_courant, &e->world);
	if (tmp)
	{
		light_add(&tmp->lights, light);
		mesh->light_id = tmp->lights.lights[tmp->lights.light_count - 1].id;
	}
}

void		ikf_item_place(t_e *e, t_mesh *mesh)
{
	if (e->editor.is_making_portail)
		mesh->sector_id = e->editor.secteur2_courant;
	if (e->editor.is_light)
		make_light(e, mesh);
	if (e->editor.is_physics)
		mesh_add_physics(mesh, (e->editor.wall_friction_is_auto)
			? -1 : e->editor.wall_friction);
	else
	{
		mesh->walls = NULL;
		mesh->nb_walls = 0;
	}
	if (e->editor.is_goal)
	{
		polygons_set_trans(mesh->polygons, mesh->polygonnum, 100);
		e->world.goal_point = (mat4vec4_multiply(mesh->matrix, (t_vec4d){.
		a = {0, 0, 0, 1.0}})).c3.vec3d;
	}
	if (e->editor.alpha != 0)
		polygons_set_trans(mesh->polygons, mesh->polygonnum,
			e->editor.alpha);
	world_add_mesh(mesh, &e->world, e->editor.secteur_courant);
}

void		kf_item_place(void *param)
{
	t_e			*e;
	t_mesh		*mesh;

	e = param;
	if (e->editor.is_modified)
		kf_item_copy(param);
	if (e->editor.item_placer && e->editor.item_placer->on_contact.id > -1 && e->editor.item_placer->on_contact.id < (int32_t)e->world.lib.nb_functions)
		libui_label_set_text(&e->editor.label_script_obj_file, e->world.lib.function_name[e->editor.item_placer->on_contact.id]);
	else
		libui_label_set_text(&e->editor.label_script_obj_file, SCRIPT_EMPTY);
	if (!e->editor.item_placer)
		return ;
	if (e->editor.is_in_view && !e->editor.is_modified)
	{
		if (e->editor.is_making_portail && e->editor.secteur_courant
		== e->editor.secteur2_courant)
			return ;
		mesh = mesh_copy(e->editor.item_placer);
		mesh->radius = get_mesh_radius(mesh);
		ikf_item_place(e, mesh);
		if (e->editor.is_making_portail)
		{
			make_portal(e);
			init_portals(&e->world);
		}
		free(mesh);
	}
}
