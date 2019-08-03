/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_editor_interface.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:41:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/07/25 15:52:39 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom-nukem.h"

void add_save_area(t_libui_widgets_surface *ws, int *control, t_editor_interface *editor_interface)
{
	SDL_Rect	rect;
	int			color;
	char		*text;

	text = "Save";
	(void)control;
	rect = (SDL_Rect){.x = 1000, .y = 10, .w = 50, .h = 50};
	color = 0xffaaaaaa;
	if (!libui_create_button(&(editor_interface->save_button), rect, color))
		printf("Error creation button\n");
	libui_widgets_add_widget(ws, &(editor_interface->save_button), 0, NULL);

	rect = (SDL_Rect){.x = 10, .y = 10, .w = 50, .h = 50};
	if (!libui_create_label(&(editor_interface->save_label), rect, text, editor_interface->font))
		printf("Error creation label\n");
	libui_widgets_add_widget(ws, &(editor_interface->save_label), 0,
							 &(editor_interface->save_button));
}

void	launch_editor_interface(t_e *e)
{
	t_libui_widgets_surface		ws;
	SDL_Event					event;
	int							control;
	t_editor_interface			editor_interface;

	libui_widgets_new_widgets_surface((SDL_Rect){0, 0,
													 LUI_DEAULT_WINDOW_WIDTH,
													 LUI_DEFAULT_WINDOW_HEIGHT},
										  &ws);
	e->win->widgets_surface = &ws;
	e->win->refresh_rate = 60;
	editor_interface.font = TTF_OpenFont("./libui/resources/Prototype.ttf", 64);
	if (editor_interface.font == NULL)
	{
		printf("Unable to load the font\n");
	}
	else
	{
		// TODO add all the parts
		// add button save area
		add_save_area(&ws, &control, &editor_interface);
		// add button select basic entity

		// add selector of file : drag and rop or select file modals

		// add modifiables values
		// TODO need checkbox
		// TODO need modifiable value : 2 buttons +1/-1 + slider?
		// TODO need slider to fit all the modidiable value
		// TODO need value group (ex: Scale, x/y/z)

		// add recap control

		// add preview
		// add 3d view
	}
	char *	dropped_filedir;
	while (1)
	{
		libui_window_clear_atomic(e->win);
		libui_widgets_draw(&ws);
		SDL_BlitSurface(ws.surface, NULL, e->win->surface, NULL);
		libui_window_refresh(e->win);
		libui_window_title(e->win, "fps: %d", e->win->fps);
		if (libui_process_events(&event))
		{
			if (event.type == SDL_QUIT
				|| (event.type == SDL_KEYDOWN
					&& event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				break;
		}
		if (event.type == SDL_DROPFILE)
		{ // In case if dropped file
			int x = 0;
			int y = 0;
			int size = 160;
			char *message;
			message = malloc(size+1);
			SDL_memset(message, '\0', size+1);
			dropped_filedir = event.drop.file;
			// Shows directory of dropped file
			SDL_GetMouseState(&x, &y);
			snprintf(message, size, "File : %s. mouse pos : x %d, y %d", dropped_filedir, x, y);
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
									 "A file droped", message, e->win->ptr);
			SDL_free(dropped_filedir); // Free dropped_filedir memory
		}
	}
	TTF_CloseFont(editor_interface.font);
}
