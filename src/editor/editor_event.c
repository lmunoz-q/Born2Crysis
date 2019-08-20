/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:20:45 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/20 14:02:43 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int editor_event(t_e *e, t_libui_widgets_surface *ws,
				  t_editor_interface *editor_interface)
{
	(void)ws;
	(void)editor_interface;
	handle_events(&e->input_map);
	/*
	SDL_Event					event;
	char *dropped_filedir;

	while (libui_process_events(&event)) // Gestion des events
	{
	
		if (event.type == SDL_QUIT
			|| (event.type == SDL_KEYDOWN
				&& event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			return (1);
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
			if (x > ws->surface->w - EDITOR_MENU_WIDTH
				&& y > ws->surface->h - 100)
			{
				snprintf(message, size, "File : %s.", dropped_filedir);
				libui_label_set_text(&(editor_interface->selected_file_label), message);
			}
			SDL_free(dropped_filedir); // Free dropped_filedir memory
		}
	}*/
	return (0);
}
