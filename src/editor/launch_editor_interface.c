/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_editor_interface.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:41:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/07/20 18:00:10 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom-nukem.h"

void	launch_editor_interface(t_e *e)
{
	t_libui_widgets_surface		ws;
	TTF_Font *					font;
	SDL_Event					event;

	libui_widgets_new_widgets_surface(
		(SDL_Rect){0, 0, LUI_DEAULT_WINDOW_WIDTH, LUI_DEFAULT_WINDOW_HEIGHT},
		&ws);
	e->win->widgets_surface = &ws;
	e->win->refresh_rate = 60;
	font = TTF_OpenFont("./libui/resources/Prototype.ttf", 64);
	if (font == NULL)
	{
		printf("Unable to load the font\n");
	}
	else
	{
		// TODO add all the parts
		// add button save area
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
	TTF_CloseFont(font);
}
