/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_editor_interface.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:41:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/14 00:38:59 by mfischer         ###   ########.fr       */
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

void	launch_editor_interface(t_e *e)
{
	t_libui_widgets_surface		ws;
	SDL_Event					event;
	t_editor_interface			editor_interface;

	libui_widgets_new_widgets_surface((SDL_Rect){0, 0,
													 LUI_DEAULT_WINDOW_WIDTH,
													 LUI_DEFAULT_WINDOW_HEIGHT},
										  &ws);
	e->win->widgets_surface = &ws;
	e->win->refresh_rate = 60;
	editor_interface.font = TTF_OpenFont("./libui/resources/Prototype.ttf", 16);
	if (editor_interface.font == NULL)
	{
		printf("Unable to load the font\n");
	}
	else
	{
		// TODO add all the parts

		if (add_container_area(&ws, &editor_interface))
			return; // TODO gerer une sortie sur erreur propre
		// add button save area
		if (add_save_area(&ws, &editor_interface))
			return ; // TODO gerer une sortie sur erreur propre
		// add button select basic entity
		if (add_basic_entity_choice(&ws, &editor_interface))
			return ; // TODO gerer une sortie sur erreur propre
		// add selector of file : drag and rop or select file modals
		if (add_selector_area(&ws, &editor_interface))
			return ; // TODO gerer une sortie sur erreur propre
		// add modifiables values
		// TODO need checkbox
		// TODO need modifiable value : 2 buttons +1/-1 + slider?
		// TODO need slider to fit all the modidiable value
		// TODO need value group (ex: Scale, x/y/z)

		// add recap control

		// add preview
		if (add_preview_area(&ws, &editor_interface))
			return ;
		// add 3d view
		if (add_view_area(&ws, &editor_interface))
			return;
	}
	char *	dropped_filedir;
	gthread_init(5, editor_interface.preview_container.texture, get_polygon_buffer(), GTHREAD_PREVIEW);
	gthread_init(20, editor_interface.view_container.texture, get_polygon_buffer(), GTHREAD_EDITOR);
	init_camera(&editor_interface.editor_cam, (t_vec2i){.n.x = editor_interface.view_container.texture->w, .n.y = editor_interface.view_container.texture->h});
	while (1)
	{
		// Affichage :
		mf_memset(get_zbuff(), 0, e->win->surface->w * e->win->surface->h * sizeof(double));
		mf_memset(ws.surface->pixels, 0, e->win->surface->w * e->win->surface->h * sizeof(Uint32));
		remplir_3dview(&editor_interface, e);
		mf_memset(get_zbuff(), 0, e->win->surface->w * e->win->surface->h * sizeof(double));
		remplir_preview(&editor_interface, e);
		libui_window_update(e->win);
		
		libui_window_title(e->win, "fps: %d", e->win->fps);
		
		if (libui_process_events(&event)) // Gestion des events
		{
			if (event.type == SDL_QUIT
				|| (event.type == SDL_KEYDOWN
					&& event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				break;
		}
		if (event.type == SDL_DROPFILE)
		{ // Gestion de la recuperation de fichier dans le recuperateur de fichier
			int   x = 0;
			int   y = 0;
			int   x2 = 0;
			int   y2 = 0;
			int size = 160;
			char *message;
			message = malloc(size+1);
			SDL_memset(message, '\0', size+1);
			dropped_filedir = event.drop.file;
			// Shows directory of dropped file
			SDL_GetGlobalMouseState(&x, &y);
			SDL_GetWindowPosition(e->win->ptr, &x2, &y2);
			x -= x2;
			y -= y2;
			printf("Released grab at x %d, y %d\n", x, y);
			if (x > ws.surface->w - EDITOR_MENU_WIDTH
				&& y > ws.surface->h - 100)
			{
				snprintf(message, size, "File : %s.", dropped_filedir);
				libui_label_set_text(&(editor_interface.selected_file_label), message);
			}
			SDL_free(dropped_filedir); // Free dropped_filedir memory
		}
		libui_window_refresh(e->win);
	}
	free_editor_interface(&editor_interface);
	TTF_CloseFont(editor_interface.font);
}
