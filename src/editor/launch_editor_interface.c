/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_editor_interface.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:41:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 20:53:49 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom_nukem.h"

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

int	save_callback(SDL_Event *event, t_libui_widget *widget, void *user_data)
{
	t_map_file	*data;
	SDL_RWops	*io;

	(void)user_data;
	(void)event;
	(void)widget;
	io = SDL_RWFromFile("test.b2cm", "wb");
	if ((data = world_to_map_file(get_world())) == NULL)
		return (0);
	SDL_RWwrite(io, data, 1, data->total_size);
	SDL_free(data);
	SDL_RWclose(io);
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
	libui_callback_setpressed(&(editor_interface->save_textbutton), save_callback, SDL_MOUSEBUTTONDOWN, NULL);
	return (0);
}

int	add_basic_entity_choice(t_libui_widgets_surface *ws, t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor cons;

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 10, .y = 10, .w = 100, .h = 50};
	cons.rect
		= (SDL_Rect){.x = 10, .y = 460, .w = 150, .h = 50};
	cons.text = "LIGHT (OFF)";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->light_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Wall.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->light_textbutton), bf_switch_light, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons.rect
		= (SDL_Rect){.x = EDITOR_MENU_WIDTH - 80, .y = 260, .w = 80, .h = 50};
	cons.text = "SPAWN";
	if (libui_create_textbutton(&(editor_interface->obj_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Obj.\n");
		return (1);
	}
	cons.rect
		= (SDL_Rect){.x = EDITOR_MENU_WIDTH - 80, .y = 320, .w = 80, .h = 50};
	cons.text = "MESH";
	editor_interface->is_making_portail = FALSE;
	if (libui_create_textbutton(&(editor_interface->portail_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Port.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->portail_textbutton), portail_pressed, SDL_MOUSEBUTTONDOWN, editor_interface);
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

int add_secteur2_selector(t_libui_widgets_surface *ws,
						 t_editor_interface *	 editor_interface)
{
	t_libui_textbutton_constructor cons;
	t_libui_callback			   callback;

	if (!libui_create_label(&(editor_interface->secteur2_selec_label),
							(SDL_Rect){.x = 40, .y = 425, .w = 195, .h = 20},
							"Secteur secondaire: 0", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->secteur2_selec_label), 0,
							 &(editor_interface->editor_container));

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 8, .y = 5, .w = 30, .h = 30};
	cons.rect = (SDL_Rect){.x = 10, .y = 420, .w = 30, .h = 30};
	cons.text = "-1";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->secteur2_selec_down_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton -1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->secteur2_selec_down_button),
							  decrease_secteur2_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	cons.rect = (SDL_Rect){.x = 235, .y = 420, .w = 30, .h = 30};
	cons.text = "+1";
	if (libui_create_textbutton(&(editor_interface->secteur2_selec_up_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton +1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->secteur2_selec_up_button),
							  increase_secteur2_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	editor_interface->secteur2_courant = 0;
	return (0);
}

int add_lux_type_selector(t_libui_widgets_surface *ws,
						  t_editor_interface *	 editor_interface)
{
	t_libui_textbutton_constructor cons;
	t_libui_callback			   callback;

	if (!libui_create_label(&(editor_interface->lux_type_label),
							(SDL_Rect){.x = 40, .y = 525, .w = 215, .h = 20},
							"Lumiere type: point", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->lux_type_label), 0,
							 &(editor_interface->editor_container));

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 7, .y = 5, .w = 30, .h = 30};
	cons.rect = (SDL_Rect){.x = 10, .y = 520, .w = 30, .h = 30};
	cons.text = "<>";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->lux_type_change_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton <>.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_type_change_button),
							  change_lux_type, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	editor_interface->lux_type = POINT_LIGHT;
	return (0);
}

int add_lux_inten_selector(t_libui_widgets_surface *ws,
						  t_editor_interface *	 editor_interface)
{
	t_libui_textbutton_constructor cons;
	t_libui_callback			   callback;

	if (!libui_create_label(&(editor_interface->lux_inten_selec_label),
							(SDL_Rect){.x = 80, .y = 565, .w = 195, .h = 20},
							"Intensite: 1", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->lux_inten_selec_label), 0,
							 &(editor_interface->editor_container));

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 7, .y = 5, .w = 50, .h = 30};
	cons.rect = (SDL_Rect){.x = 50, .y = 560, .w = 30, .h = 30};
	cons.text = "-1";
	cons.ws = ws;
	if (libui_create_textbutton(
			&(editor_interface->lux_inten_selec_down_button), &cons))
	{
		printf("Error lors de la creation du textbouton -1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_inten_selec_down_button),
							  decrease_lux_inten_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	cons.rect = (SDL_Rect){.x = 275, .y = 560, .w = 30, .h = 30};
	cons.text = "+1";
	if (libui_create_textbutton(&(editor_interface->lux_inten_selec_up_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton +1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_inten_selec_up_button),
							  increase_lux_inten_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	cons.rect = (SDL_Rect){.x = 310, .y = 560, .w = 45, .h = 30};
	cons.text = "+10";
	if (libui_create_textbutton(&(editor_interface->lux_inten_selec_up10_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton +10.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_inten_selec_up10_button),
							  increase10_lux_inten_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	cons.rect = (SDL_Rect){.x = 10, .y = 560, .w = 35, .h = 30};
	cons.text = "-10";
	if (libui_create_textbutton(
			&(editor_interface->lux_inten_selec_down10_button), &cons))
	{
		printf("Error lors de la creation du textbouton -10.\n");
		return (1);
	}
	libui_callback_setpressed(
		&(editor_interface->lux_inten_selec_down10_button),
		decrease10_lux_inten_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	editor_interface->lux_intensity = 1.0;
	return (0);
}

int add_lux_fallof_selector(t_libui_widgets_surface *ws,
						   t_editor_interface *		editor_interface)
{
	t_libui_textbutton_constructor cons;
	t_libui_callback			   callback;

	if (!libui_create_label(&(editor_interface->lux_fallof_selec_label),
							(SDL_Rect){.x = 80, .y = 605, .w = 195, .h = 20},
							"FallOf: 1", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->lux_fallof_selec_label), 0,
							 &(editor_interface->editor_container));

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 7, .y = 5, .w = 50, .h = 30};
	cons.rect = (SDL_Rect){.x = 50, .y = 600, .w = 30, .h = 30};
	cons.text = "-1";
	cons.ws = ws;
	if (libui_create_textbutton(
			&(editor_interface->lux_fallof_selec_down_button), &cons))
	{
		printf("Error lors de la creation du textbouton -1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_fallof_selec_down_button),
							  decrease_lux_fallof_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	cons.rect = (SDL_Rect){.x = 275, .y = 600, .w = 30, .h = 30};
	cons.text = "+1";
	if (libui_create_textbutton(&(editor_interface->lux_fallof_selec_up_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton +1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_fallof_selec_up_button),
							  increase_lux_fallof_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	cons.rect = (SDL_Rect){.x = 310, .y = 600, .w = 45, .h = 30};
	cons.text = "+0.1";
	if (libui_create_textbutton(
			&(editor_interface->lux_fallof_selec_upDot1_button), &cons))
	{
		printf("Error lors de la creation du textbouton +0.1.\n");
		return (1);
	}
	libui_callback_setpressed(
		&(editor_interface->lux_fallof_selec_upDot1_button),
		increaseDot1_lux_fallof_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons.rect = (SDL_Rect){.x = 10, .y = 600, .w = 35, .h = 30};
	cons.text = "-0.1";
	if (libui_create_textbutton(
			&(editor_interface->lux_fallof_selec_downDot1_button), &cons))
	{
		printf("Error lors de la creation du textbouton -0.1.\n");
		return (1);
	}
	libui_callback_setpressed(
		&(editor_interface->lux_fallof_selec_downDot1_button),
		decreaseDot1_lux_fallof_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	editor_interface->lux_fallof = 1.0;
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
	(void)e;
	if (!libui_create_container(&(editor_interface->view_container),
								(SDL_Rect){.x = 0,
										   .y = 0,
										   .w = ws->surface->w - EDITOR_MENU_WIDTH,
										   .h = ws->surface->h},
								0xffaaaaaa))
		return (1);
	//libui_callback_setpressed(&(editor_interface->view_container),
						//	  toggle_capture_mouse, SDL_MOUSEBUTTONDOWN,
						//	  e->win->ptr);
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
		mat4_tmp = ((t_mesh *)editor_interface->item_placer)->matrix;
		((t_mesh *)editor_interface->item_placer)->matrix = editor_interface->preview_mat;
		render_preview(editor_interface->item_placer, editor_interface->preview_container.texture,
		(t_vec2i){.a = {editor_interface->preview_container.texture->w, editor_interface->preview_container.texture->h}});
		((t_mesh *)editor_interface->item_placer)->matrix = mat4_tmp;
		editor_interface->preview_container.need_redraw = 1;
	}
}

void remplir_3dview(t_editor_interface *editor_interface, t_e *e)
{
	t_vec3d		tmp;
	double		new_radius;
	int			i;
	int			y;

	gthread_get(GTHREAD_EDITOR);
	editor_interface->view_container.need_redraw = 1;
	render_editor_view(&e->world, editor_interface);
	mat4_init(&editor_interface->item_mat);
	if (!editor_interface->item_placer)
		return ;
	editor_interface->item_placer->matrix = editor_interface->item_scale_mat;
	new_radius = get_mesh_radius(editor_interface->item_placer) + 15;
	tmp = vec3vec3_substract(editor_interface->editor_cam.pos,
	vec3scalar_multiply(editor_interface->editor_cam.view_dir, (new_radius > 15) ? new_radius : 15));
	editor_interface->item_placer->matrix = mat4mat4_multiply(((t_mesh *)editor_interface->item_placer)->matrix , editor_interface->item_rotation_mat);
	editor_interface->item_placer->matrix = mat4_translate(((t_mesh *)editor_interface->item_placer)->matrix, tmp.n.x, tmp.n.y, tmp.n.z);
	render_mesh(editor_interface->item_placer, &editor_interface->editor_cam, editor_interface->view_container.texture, NULL);
	i = editor_interface->view_container.texture->w / 2 - 5;
	y = editor_interface->view_container.texture->h / 2;
	while (i < editor_interface->view_container.texture->w / 2 + 5)
	{
		((int *)(editor_interface->view_container.texture->pixels))[y * editor_interface->view_container.texture->w + i] = 0xffffffff;
		i++;
	}
	i = editor_interface->view_container.texture->w / 2;
	y = editor_interface->view_container.texture->h / 2 - 5;
	while (y < editor_interface->view_container.texture->h / 2 + 5)
	{
		((int *)(editor_interface->view_container.texture
			->pixels))[y * editor_interface->view_container.texture->w + i]
			= 0xffffffff;
		y++;
	}
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
	editor_interface->is_making_portail = 1;
	editor_interface->font = TTF_OpenFont("./libui/resources/Prototype.ttf", 16);
	init_default_editor_controls(&e->input_map, e);
	init_zbuff(ws->surface->h * ws->surface->w);
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
		if (add_secteur2_selector(ws, editor_interface))
			return;
		if (add_lux_type_selector(ws, editor_interface))
			return;
		if (add_lux_inten_selector(ws, editor_interface))
			return;
		if (add_lux_fallof_selector(ws, editor_interface))
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
	editor_interface->is_in_view = FALSE;
	editor_interface->is_light = FALSE;
	editor_interface->item_placer = NULL;
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
