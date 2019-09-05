/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_editor_elements_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:43:25 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/04 15:02:52 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

int		add_container_area(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
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

int		save_callback(SDL_Event *event, t_libui_widget *widget,
	void *user_data)
{
	t_map_file	*data;
	SDL_RWops	*io;
	t_world		*w;

	(void)user_data;
	(void)event;
	(void)widget;
	if ((w = get_world()) == NULL)
		mf_printf("Invalid world\n");
	else if (w->skybox == NULL || w->textures == NULL || w->nb_textures == 0)
		mf_printf("Missing skybox\n");
	else if (link_library(&w->lib, 1) == ET_OK)
	{
		io = SDL_RWFromFile((char *)user_data, "wb");
		if ((data = world_to_map_file(get_world())) == NULL)
			return (0);
		SDL_RWwrite(io, data, 1, data->total_size);
		SDL_free(data);
		SDL_RWclose(io);
	}
	return (0);
}

int		add_save_area(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor	cons;

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 10, .y = 10, .w = 50, .h = 50};
	cons.rect = (SDL_Rect)
		{.x = EDITOR_MENU_WIDTH - 50, .y = 10, .w = 50, .h = 50};
	cons.text = "Save";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->save_textbutton), &cons))
		return (1);
	cons.rect = (SDL_Rect)
		{.x = EDITOR_MENU_WIDTH - 50, .y = 70, .w = 50, .h = 50};
	cons.text = "New";
	if (libui_create_textbutton(&(editor_interface->new_textbutton), &cons))
		return (1);
	libui_callback_setpressed(&(editor_interface->save_textbutton),
		save_callback, SDL_MOUSEBUTTONDOWN, editor_interface->path);
	return (0);
}
