/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:51:45 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/30 13:52:08 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void init_editor(t_e *e, t_libui_widgets_surface *ws,
				 t_editor_interface		*editor_interface)
{
	libui_widgets_new_widgets_surface(
		(SDL_Rect){0, 0, LUI_DEAULT_WINDOW_WIDTH, LUI_DEFAULT_WINDOW_HEIGHT},
		ws);
	e->win->widgets_surface = ws;
	e->win->refresh_rate = 60;
	e->editor_running = TRUE;
	editor_interface->is_making_portail = 1;
	editor_interface->font = TTF_OpenFont("./libui/resources/Prototype.ttf", 16);
	init_default_editor_controls(&e->input_map, e);
	init_zbuff(ws->surface->h * ws->surface->w);
	editor_interface->sector_gravity = (t_vec3d){.a = {0, -1.2, 0}};
	editor_interface->sector_global_friction = (t_vec3d){.a = {1, 1.0, 1}};
	editor_interface->sector_drag = (t_vec3d){.a = {0.95, 1, 0.95}};
	editor_interface->sector_speed_limit = 0.80;
	if (editor_interface->font == NULL)// Avant cette ligne 1 leak 288xxxxxxxx
	{
		printf("Unable to load the font\n");
	}
	else
	{
		// TODO add all the parts

		if (add_container_area(ws, editor_interface))
			return; // TODO gerer une sortie sur erreur propre
		// add button save area
		if (add_save_area(ws, editor_interface))
			return; // TODO gerer une sortie sur erreur propre
		// add button select basic entity
		if (add_basic_entity_choice(ws, editor_interface, e))
			return; // TODO gerer une sortie sur erreur propre
		// add selector of file : drag and rop or select file modals
		if (add_selector_area(ws, editor_interface))
			return; // TODO gerer une sortie sur erreur propre
		// add choix secteur
		if (add_secteur_selector(ws, editor_interface, e))
			return;
		if (add_secteur2_selector(ws, editor_interface, e))
			return;
		if (add_lux_type_selector(ws, editor_interface))
			return;
		if (add_lux_inten_selector(ws, editor_interface))
			return;
		if (add_lux_fallof_selector(ws, editor_interface))
			return;
		if (add_physics_button(ws, editor_interface))
			return;
		if (add_sliders_physics_gravity(ws, editor_interface))
			return;
		if (add_sliders_physics_gbl_fric(ws, editor_interface))
			return;
		if (add_sliders_physics_drag(ws, editor_interface))
			return;
		if (add_slider_alpha(ws, editor_interface))
			return;
		if (add_save_file_input(ws, editor_interface))
		{
			printf("ah bah pas de input\n");
			return;
		}
		// add recap control

		// add preview
		if (add_preview_area(ws, editor_interface)) // avant cette ligne 1 leak
			return;
		// add 3d view
		if (add_view_area(ws, editor_interface, e))
			return;
	}// toujours 1 leak
	gthread_init(4, editor_interface->preview_container.texture,
				 get_polygon_buffer(), GTHREAD_PREVIEW);
	gthread_init(20, editor_interface->view_container.texture,
				 get_polygon_buffer(), GTHREAD_EDITOR);
	init_camera(&editor_interface->editor_cam,// toujours 1 leak
				(t_vec2i){.n.x = editor_interface->view_container.texture->w,
						  .n.y = editor_interface->view_container.texture->h});
	mat4_init(&editor_interface->preview_mat);
	editor_interface->preview_mat = mat4_translate(editor_interface->preview_mat, 0, -10, 0);
	mat4_init(&editor_interface->item_mat);
	mat4_init(&editor_interface->item_scale_mat);
	// mat4_init(&editor_interface->item_rotation_mat);
	editor_interface->item_rotation = (t_vec4d){{0, 0, 0, 1}};// toujours 1 leak
	editor_interface->is_in_view = FALSE;
	editor_interface->is_light = FALSE;
	editor_interface->is_goal = FALSE;
	editor_interface->alpha = 0;
	editor_interface->item_placer = NULL;
	if (!e->world.sectors) // toujours 1 leak
	{
		sector_create(&e->world);
		e->world.sectors[editor_interface->secteur_courant].physics.drag = editor_interface->sector_drag;
		e->world.sectors[editor_interface->secteur_courant].physics.gravity = editor_interface->sector_gravity;
		e->world.sectors[editor_interface->secteur_courant].physics.global_friction = editor_interface->sector_global_friction;
		e->world.sectors[editor_interface->secteur_courant].physics.speed_limit = editor_interface->sector_speed_limit;
		e->world.sectors[editor_interface->secteur_courant].physics.entering_effet = EFF_NOTHING;
		e->world.sectors[editor_interface->secteur_courant].physics.leaving_effect = EFF_NOTHING;
		e->world.sectors[editor_interface->secteur_courant].physics.frame_effect = EFF_NOTHING;
		t_mesh *tmp_mesh = obj_to_mesh( // avant yen a 2, donc 1 de plus
			object_manager_get_obj("assets/objects/crate.obj"), "assets/textures/gold_tex.bmp", TX_CLAMP_EDGES);
		tmp_mesh->matrix = mat4_translate(tmp_mesh->matrix, 0, -8, 0);
		tmp_mesh->matrix = mat4_scale(tmp_mesh->matrix, 2, 1, 2);
		mesh_add_physics(tmp_mesh);// avant cette ligne y'en a  5, donc 3 de plus, mais pas toujours des fois toujours 2 ?? wtf ??? 
		if (tmp_mesh)
			world_add_mesh(tmp_mesh, &e->world, 0);
	} // Des fois les leaks apparaisse plus tard
}
