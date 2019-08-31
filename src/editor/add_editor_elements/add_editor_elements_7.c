/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_editor_elements_7.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:12:50 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/31 16:10:14 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

int		add_physics_button(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor cons;

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 10, .y = 10, .w = 120, .h = 50};
	cons.rect = (SDL_Rect){.x = 10, .y = 610, .w = 150, .h = 50};
	cons.text = "PHYSICS (OFF)";
	cons.ws = ws;
	editor_interface->is_physics = FALSE;
	if (libui_create_textbutton(&(editor_interface->physics_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Wall.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->physics_textbutton),
		bf_switch_physics, SDL_MOUSEBUTTONDOWN, editor_interface);
	return (0);
}

int		add_preview_area(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	if (!libui_create_container(&(editor_interface->preview_container),
		(SDL_Rect){.x = 0,
			.y = 30,
			.w = EDITOR_MENU_WIDTH - 100,
			.h = 270},
			0xffaaaaaa))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->preview_container), 0,
		&(editor_interface->editor_container));
	return (0);
}

int		add_view_area(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
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
