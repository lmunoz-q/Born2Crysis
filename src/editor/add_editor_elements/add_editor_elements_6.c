/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_editor_elements_6.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:00:16 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/30 13:01:46 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

int		add_lux_type_selector(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor cons;

	if (!libui_create_label(&(editor_interface->lux_type_label),
		(SDL_Rect){.x = 40, .y = 480, .w = 215, .h = 20},
		"Lumiere type: point", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->lux_type_label), 0,
		&(editor_interface->editor_container));
	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 7, .y = 5, .w = 30, .h = 30};
	cons.rect = (SDL_Rect){.x = 10, .y = 475, .w = 30, .h = 30};
	cons.text = "<>";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->lux_type_change_button),
		&cons))
	{
		mf_printf("Error lors de la creation du textbouton <>.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_type_change_button),
		change_lux_type, SDL_MOUSEBUTTONDOWN, editor_interface);
	editor_interface->lux_type = POINT_LIGHT;
	return (0);
}
