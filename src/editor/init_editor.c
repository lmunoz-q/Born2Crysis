/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:51:45 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/05 11:17:26 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

static int	add_elements1(t_e *e, t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	if (add_container_area(ws, editor_interface))
		return (-1);
	if (add_save_area(ws, editor_interface))
		return (-1);
	if (add_basic_entity_choice(ws, editor_interface, e))
		return (-1);
	if (add_selector_area(ws, editor_interface))
		return (-1);
	if (add_secteur_selector(ws, editor_interface, e))
		return (-1);
	if (add_secteur2_selector(ws, editor_interface, e))
		return (-1);
	if (add_lux_type_selector(ws, editor_interface))
		return (-1);
	if (add_lux_inten_selector(ws, editor_interface))
		return (-1);
	if (add_lux_fallof_selector(ws, editor_interface))
		return (-1);
	if (add_physics_button(ws, editor_interface))
		return (-1);
	return (0);
}

static int	add_elements2(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	if (add_sliders_physics_gravity(ws, editor_interface)
			|| add_sliders_physics_gbl_fric(ws, editor_interface)
			|| add_sliders_physics_drag(ws, editor_interface))
		return (-1);
	if (add_slider_alpha(ws, editor_interface))
		return (-1);
	if (add_save_file_input(ws, editor_interface))
		return (-1);
	if (add_preview_area(ws, editor_interface))
		return (-1);
	if (add_view_area(ws, editor_interface))
		return (-1);
	if (add_precision_slider_physics_gravity_up(ws, editor_interface))
		return (-1);
	if (add_precision_slider_physics_drag_up(ws, editor_interface))
		return (-1);
	if (add_precision_slider_physics_friction_up(ws, editor_interface))
		return (-1);
	if (add_precision_slider_physics_gravity_down(ws, editor_interface))
		return (-1);
	if (add_precision_slider_physics_drag_down(ws, editor_interface))
		return (-1);
	if (add_precision_slider_physics_friction_down(ws, editor_interface))
		return (-1);
	return (0);
}

static int	add_elements3(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	if (add_wall_friction(ws, editor_interface))
		return (-1);
	if (add_precision_wall_friction(ws, editor_interface))
		return (-1);
	editor_interface->is_modified = FALSE;
	if (add_script_area(ws, editor_interface))
		return (-1);
	
	return (0);
}

static void	edi_init_world(t_e *e, t_editor_interface *editor_interface)
{
	t_mesh *tmp_mesh;

	sector_create(&e->world);
	e->world.sectors[editor_interface->secteur_courant]
		.physics.drag = editor_interface->sector_drag;
	e->world.sectors[editor_interface->secteur_courant]
		.physics.gravity = editor_interface->sector_gravity;
	e->world.sectors[editor_interface->secteur_courant]
		.physics.global_friction = editor_interface->sector_global_friction;
	e->world.sectors[editor_interface->secteur_courant]
		.physics.speed_limit = editor_interface->sector_speed_limit;
	e->world.sectors[editor_interface->secteur_courant]
		.physics.entering_effect = (t_effet){-1, {0}};
	e->world.sectors[editor_interface->secteur_courant]
		.physics.leaving_effect = (t_effet){-1, {0}};
	e->world.sectors[editor_interface->secteur_courant]
		.physics.frame_effect = (t_effet){-1, {0}};
	tmp_mesh = obj_to_mesh(
		object_manager_get_obj("assets/objects/crate.obj"),
			"assets/textures/gold_tex.bmp", TX_CLAMP_EDGES);
	tmp_mesh->matrix = mat4_translate(tmp_mesh->matrix, 0, -8, 0);
	tmp_mesh->matrix = mat4_scale(tmp_mesh->matrix, 2, 1, 2);
	mesh_add_physics(tmp_mesh, -1);
	if (tmp_mesh)
		world_add_mesh(tmp_mesh, &e->world, 0);
}

int			init_editor(t_e *e, t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	editor_init_value1(e, ws, editor_interface);
	if (editor_interface->font == NULL)
	{
		printf("Unable to load the font\n");
		return (-1);
	}
	else
	{
		if (add_elements1(e, ws, editor_interface))
			return (-1);
		if (add_elements2(ws, editor_interface))
			return (-1);
		if (add_elements3(ws, editor_interface))
			return (-1);
	}
	editor_init_value2(editor_interface);
	if (!e->world.sectors)
		edi_init_world(e, editor_interface);
	return (0);
}
