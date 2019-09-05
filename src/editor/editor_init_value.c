/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_init_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 15:58:32 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/05 17:02:53 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

void	editor_init_value1(t_e *e, t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	libui_widgets_new_widgets_surface(
		(SDL_Rect){0, 0, LUI_DEAULT_WINDOW_WIDTH, LUI_DEFAULT_WINDOW_HEIGHT},
		ws);
	e->win->widgets_surface = ws;
	e->win->refresh_rate = 60;
	e->editor_running = TRUE;
	editor_interface->is_making_portail = 1;
	editor_interface->font =
		TTF_OpenFont("./libui/resources/Prototype.ttf", 16);
	init_default_editor_controls(&e->input_map, e);
	init_zbuff(ws->surface->h * ws->surface->w);
	editor_interface->sector_speed_limit = 0.80;
	editor_interface->wall_friction_is_auto = SDL_FALSE;
}

void	editor_init_value2(t_editor_interface *editor_interface)
{
	gthread_init(4, editor_interface->preview_container.texture,
		get_polygon_buffer(), GTHREAD_PREVIEW);
	gthread_init(20, editor_interface->view_container.texture,
		get_polygon_buffer(), GTHREAD_EDITOR);
	init_camera(&editor_interface->editor_cam,
		(t_vec2i){.n.x = editor_interface->view_container.texture->w,
			.n.y = editor_interface->view_container.texture->h});
	mat4_init(&editor_interface->preview_mat);
	editor_interface->preview_mat = mat4_translate(
		editor_interface->preview_mat, 0, -10, 0);
	mat4_init(&editor_interface->item_mat);
	mat4_init(&editor_interface->item_scale_mat);
	editor_interface->item_rotation = (t_vec4d){{0, 0, 0, 1}};
	editor_interface->is_in_view = FALSE;
	editor_interface->is_light = FALSE;
	editor_interface->is_goal = FALSE;
	editor_interface->alpha = 0;
	editor_interface->item_placer = NULL;
	editor_interface->script_obj_path = NULL;
	if (!get_env()->world.sectors)
	{
		editor_interface->sector_gravity = (t_vec3d){.a = {0, -1.2, 0}};
		editor_interface->sector_global_friction = (t_vec3d){.a = {1, 1.0, 1}};
		editor_interface->sector_drag = (t_vec3d){.a = {0.95, 1, 0.95}};
	}
	else
	{
		editor_interface->secteur_courant = 0;
		update_editor_interface_secteur(get_env(), editor_interface);
	}
}
