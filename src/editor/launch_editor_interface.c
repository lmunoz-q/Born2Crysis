/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_editor_interface.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:41:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/14 17:44:43 by mfischer         ###   ########.fr       */
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

int add_preview_area(t_libui_widgets_surface *ws,
					 t_editor_interface *	 editor_interface)
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
					 t_editor_interface *	 editor_interface)
{
	if (!libui_create_container(&(editor_interface->view_container),
								(SDL_Rect){.x = 0,
										   .y = 0,
										   .w = ws->surface->w - EDITOR_MENU_WIDTH,
										   .h = ws->surface->h},
								0xffaaaaaa))
		return (1);
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
	//la texture du la preview :
	//editor_interface->preview_container.texture
	// texture de la view
	//editor_interface->view_container.texture
	gthread_get(GTHREAD_PREVIEW);
	render_object_preview(&e->world.sectors[0].objects[3], editor_interface->preview_container.texture,
	(t_vec2i){.a = {editor_interface->preview_container.texture->w, editor_interface->preview_container.texture->h}});
	editor_interface->preview_container.need_redraw = 1;
}

void remplir_3dview(t_editor_interface *editor_interface, t_e *e)
{
	gthread_get(GTHREAD_EDITOR);
	render_editor_view(&e->world, editor_interface);
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
		// add modifiables values
		// TODO need checkbox
		// TODO need modifiable value : 2 buttons +1/-1 + slider?
		// TODO need slider to fit all the modidiable value
		// TODO need value group (ex: Scale, x/y/z)

		// add recap control

		// add preview
		if (add_preview_area(ws, editor_interface))
			return;
		// add 3d view
		if (add_view_area(ws, editor_interface))
			return;
	}
	gthread_init(5, editor_interface->preview_container.texture,
				 get_polygon_buffer(), GTHREAD_PREVIEW);
	gthread_init(20, editor_interface->view_container.texture,
				 get_polygon_buffer(), GTHREAD_EDITOR);
	init_camera(&editor_interface->editor_cam,
				(t_vec2i){.n.x = editor_interface->view_container.texture->w,
						  .n.y = editor_interface->view_container.texture->h});
}

void close_editor(t_editor_interface *editor_interface)
{

	free_editor_interface(editor_interface);
	TTF_CloseFont(editor_interface->font);
}

void	launch_editor_interface(t_e *e)
{
	t_libui_widgets_surface		ws;
	t_editor_interface			editor_interface;
	uint32_t	last_frame;
	double		elapsed_time;
	uint32_t	tmp;

	init_editor(e, &ws, &editor_interface);
	elapsed_time = 0;
	last_frame = SDL_GetTicks();
	while (e->editor_running)
	{
		while (elapsed_time >= DELTATIME)
		{
			if (editor_event(e, &ws, &editor_interface))
				e->editor_running = FALSE;
			printf("fps = %i\n", e->stats.fps);
			elapsed_time -= DELTATIME;
			//update logic
		}
		editor_render(e, &ws, &editor_interface);
		tmp = SDL_GetTicks();
		elapsed_time += (double)(tmp - last_frame) / 1000.0;
		last_frame = tmp;
		count_fps(&e->stats.fps);
	}
	close_editor(&editor_interface);
}