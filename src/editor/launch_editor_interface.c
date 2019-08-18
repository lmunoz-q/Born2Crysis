/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_editor_interface.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:41:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/18 21:21:03 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom-nukem.h"

int add_container_area(t_libui_widgets_surface *ws, t_editor_interface *editor_interface)
{
	if (!libui_create_container(
			&(editor_interface->editor_container),
			(SDL_Rect){.x = ws->surface->w - EDITOR_MENU_WIDTH,
					   .y = 0,
					   .w = EDITOR_MENU_WIDTH,
					   .h = ws->surface->h},
			0xff444444))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->editor_container), 0,
							 NULL);
	return (0);
}

int add_save_area(t_libui_widgets_surface *ws, t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor	cons;

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 10, .y = 10, .w = 50, .h = 50};
	cons.rect
		= (SDL_Rect){.x = EDITOR_MENU_WIDTH - 50, .y = 10, .w = 50, .h = 50};
	cons.text = "Save";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->save_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Save.\n");
		return (1);
	}
	cons.rect
		= (SDL_Rect){.x = EDITOR_MENU_WIDTH - 50, .y = 70, .w = 50, .h = 50};
	cons.text = "New";
	if (libui_create_textbutton(&(editor_interface->new_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton New.\n");
		return (1);
	}
	return (0);
}

int	add_basic_entity_choice(t_libui_widgets_surface *ws, t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor cons;

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 10, .y = 10, .w = 50, .h = 50};
	cons.rect
		= (SDL_Rect){.x = EDITOR_MENU_WIDTH - 50, .y = 200, .w = 50, .h = 50};
	cons.text = "Wall";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->wall_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Wall.\n");
		return (1);
	}
	cons.rect
		= (SDL_Rect){.x = EDITOR_MENU_WIDTH - 50, .y = 260, .w = 50, .h = 50};
	cons.text = "OBJ";
	if (libui_create_textbutton(&(editor_interface->obj_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Obj.\n");
		return (1);
	}
	return (0);
}

int	add_selector_area(t_libui_widgets_surface *ws,
				  t_editor_interface *	 editor_interface)
{
	if (!libui_create_container(
			&(editor_interface->select_container),
			(SDL_Rect){.x = 0,
					   .y = ws->surface->h - 100,
					   .w = EDITOR_MENU_WIDTH,
					   .h = 100},
			0xffaaaaaa))
		return (1);
	if (!libui_create_label(
			&(editor_interface->selected_file_label),
			(SDL_Rect){.x = 10, .y = 75, .w = EDITOR_MENU_WIDTH - 20, .h = 20},
			"\"No file selected\"", editor_interface->font))
		return (1);
	if (!libui_create_label(
			&(editor_interface->select_label),
			(SDL_Rect){.x = 10, .y = 10, .w = EDITOR_MENU_WIDTH - 20, .h = 20},
			"File selector", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->select_container), 0,
							 &(editor_interface->editor_container));
	libui_widgets_add_widget(ws, &(editor_interface->selected_file_label), 0,
							 &(editor_interface->select_container));
	libui_widgets_add_widget(ws, &(editor_interface->select_label), 0,
							 &(editor_interface->select_container));
	return (0);
}

int add_secteur_selector(t_libui_widgets_surface *ws,
						 t_editor_interface *	 editor_interface)
{
	t_libui_textbutton_constructor cons;
	t_libui_callback			callback;

	if (!libui_create_label(
			&(editor_interface->secteur_selec_label),
			(SDL_Rect){
				.x = 40, .y = 325, .w = 175, .h = 20},
			"Secteur courant: 0", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->secteur_selec_label), 0,
							 &(editor_interface->editor_container));

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 8, .y = 5, .w = 30, .h = 30};
	cons.rect
		= (SDL_Rect){.x = 10, .y = 320, .w = 30, .h = 30};
	cons.text = "-1";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->secteur_selec_down_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton -1.\n");
		return (1);
	}
	libui_callback_setpressed(
		&(editor_interface->secteur_selec_down_button), decrease_secteur_number,
		SDL_MOUSEBUTTONDOWN, editor_interface);
	cons.rect = (SDL_Rect){.x = 215, .y = 320, .w = 30, .h = 30};
	cons.text = "+1";
	if (libui_create_textbutton(&(editor_interface->secteur_selec_up_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton +1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->secteur_selec_up_button),
							  increase_secteur_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	editor_interface->secteur_courant = 0;
	return (0);
}

int add_preview_area(t_libui_widgets_surface *ws,
					 t_editor_interface *editor_interface)
{
	if (!libui_create_container(&(editor_interface->preview_container),
								(SDL_Rect){.x = 0,
										   .y = 10,
										   .w = EDITOR_MENU_WIDTH - 100,
										   .h = 300},
								0xffaaaaaa))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->preview_container), 0,
							 &(editor_interface->editor_container));
	return (0);
}

int add_view_area(t_libui_widgets_surface *ws,
				  t_editor_interface *editor_interface, t_e *e)
{
	if (!libui_create_container(&(editor_interface->view_container),
								(SDL_Rect){.x = 0,
										   .y = 0,
										   .w = ws->surface->w - EDITOR_MENU_WIDTH,
										   .h = ws->surface->h},
								0xffaaaaaa))
		return (1);
	libui_callback_setpressed(&(editor_interface->view_container),
							  toggle_capture_mouse, SDL_MOUSEBUTTONDOWN,
							  e->win->ptr);
	libui_widgets_add_widget(ws, &(editor_interface->view_container), 0,
							NULL);
	return (0);
}

void	free_editor_interface(t_editor_interface *editor_interface)
{
	(void)editor_interface;
}

void remplir_preview(t_editor_interface *editor_interface, t_e *e)
{
	t_mat4d		mat4_tmp;
	
	(void)e;
	gthread_get(GTHREAD_PREVIEW);
	if (editor_interface->item_placer)
	{
		if (editor_interface->is_object)
		{
			mat4_tmp = ((t_object *)editor_interface->item_placer)->mesh->matrix;
			((t_object *)editor_interface->item_placer)->mesh->matrix = editor_interface->preview_mat;
			render_preview(((t_object *)editor_interface->item_placer)->mesh, editor_interface->preview_container.texture,
				(t_vec2i){.a = {editor_interface->preview_container.texture->w, editor_interface->preview_container.texture->h}});
			((t_object *)editor_interface->item_placer)->mesh->matrix = mat4_tmp;
		}
		else
		{
			mat4_tmp = ((t_mesh *)editor_interface->item_placer)->matrix;
			((t_mesh *)editor_interface->item_placer)->matrix = editor_interface->preview_mat;
			render_preview(editor_interface->item_placer, editor_interface->preview_container.texture,
				(t_vec2i){.a = {editor_interface->preview_container.texture->w, editor_interface->preview_container.texture->h}});
			((t_mesh *)editor_interface->item_placer)->matrix = mat4_tmp;
		}
		editor_interface->preview_container.need_redraw = 1;
	}
}

void remplir_3dview(t_editor_interface *editor_interface, t_e *e)
{
	t_vec3d		tmp;
	double		new_radius;

	gthread_get(GTHREAD_EDITOR);
	render_editor_view(&e->world, editor_interface);
	mat4_init(&editor_interface->item_mat);
	if (editor_interface->is_object)
	{
		((t_object *)editor_interface->item_placer)->mesh->matrix = editor_interface->item_scale_mat;
		new_radius = get_mesh_radius(((t_object *)editor_interface->item_placer)->mesh);
		tmp = vec3vec3_substract(editor_interface->editor_cam.pos,
		vec3scalar_multiply(editor_interface->editor_cam.view_dir, (new_radius > 15) ? new_radius : 15));
		((t_object *)editor_interface->item_placer)->mesh->matrix = mat4mat4_multiply(((t_object *)editor_interface->item_placer)->mesh->matrix , editor_interface->item_rotation_mat);
		((t_object *)editor_interface->item_placer)->mesh->matrix = mat4_translate(((t_object *)editor_interface->item_placer)->mesh->matrix, tmp.n.x, tmp.n.y, tmp.n.z);
		render_object(editor_interface->item_placer, &editor_interface->editor_cam, editor_interface->view_container.texture, NULL);
	}
	else
	{
		((t_mesh *)editor_interface->item_placer)->matrix = editor_interface->item_scale_mat;
		new_radius = get_mesh_radius(editor_interface->item_placer);
		tmp = vec3vec3_substract(editor_interface->editor_cam.pos,
		vec3scalar_multiply(editor_interface->editor_cam.view_dir, (new_radius > 15) ? new_radius : 15));
		((t_mesh *)editor_interface->item_placer)->matrix = mat4mat4_multiply(((t_mesh *)editor_interface->item_placer)->matrix , editor_interface->item_rotation_mat);
		((t_mesh *)editor_interface->item_placer)->matrix = mat4_translate(((t_mesh *)editor_interface->item_placer)->matrix, tmp.n.x, tmp.n.y, tmp.n.z);
		render_mesh(editor_interface->item_placer, &editor_interface->editor_cam, editor_interface->view_container.texture, NULL);
	}
	editor_interface->view_container.need_redraw = 1;
}

void init_editor(t_e *e, t_libui_widgets_surface *ws,
				 t_editor_interface		*editor_interface)
{
	libui_widgets_new_widgets_surface(
		(SDL_Rect){0, 0, LUI_DEAULT_WINDOW_WIDTH, LUI_DEFAULT_WINDOW_HEIGHT},
		ws);
	e->win->widgets_surface = ws;
	e->win->refresh_rate = 60;
	e->editor_running = TRUE;
	editor_interface->font = TTF_OpenFont("./libui/resources/Prototype.ttf", 16);
	init_default_editor_controls(&e->input_map, e);
	if (editor_interface->font == NULL)
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
		if (add_basic_entity_choice(ws, editor_interface))
			return; // TODO gerer une sortie sur erreur propre
		// add selector of file : drag and rop or select file modals
		if (add_selector_area(ws, editor_interface))
			return; // TODO gerer une sortie sur erreur propre
		// add choix secteur
		if (add_secteur_selector(ws, editor_interface))
			return;
		// add recap control

		// add preview
		if (add_preview_area(ws, editor_interface))
			return;
		// add 3d view
		if (add_view_area(ws, editor_interface, e))
			return;
	}
	gthread_init(4, editor_interface->preview_container.texture,
				 get_polygon_buffer(), GTHREAD_PREVIEW);
	gthread_init(20, editor_interface->view_container.texture,
				 get_polygon_buffer(), GTHREAD_EDITOR);
	init_camera(&editor_interface->editor_cam,
				(t_vec2i){.n.x = editor_interface->view_container.texture->w,
						  .n.y = editor_interface->view_container.texture->h});
	mat4_init(&editor_interface->preview_mat);
	editor_interface->preview_mat = mat4_translate(editor_interface->preview_mat, 0, -10, 0);
	mat4_init(&editor_interface->item_mat);
	mat4_init(&editor_interface->item_scale_mat);
	mat4_init(&editor_interface->item_rotation_mat);
}

void close_editor(t_editor_interface *editor_interface)
{

	free_editor_interface(editor_interface);
	TTF_CloseFont(editor_interface->font);
}

void	launch_editor_interface(t_e *e)
{
	t_libui_widgets_surface		ws;
	uint32_t	last_frame;
	double		elapsed_time;
	uint32_t	tmp;

	init_editor(e, &ws, &e->editor);
	elapsed_time = 0;
	last_frame = SDL_GetTicks();
	while (e->editor_running)
	{
		while (elapsed_time >= DELTATIME)
		{
			editor_event(e, &ws, &e->editor);
			editor_update(e, &ws, &e->editor);
			elapsed_time -= DELTATIME;
		}
		editor_render(e, &ws, &e->editor);
		tmp = SDL_GetTicks();
		elapsed_time += (double)(tmp - last_frame) / 1000.0;
		last_frame = tmp;
		count_fps(&e->stats.fps);
	}
	close_editor(&e->editor);
}
