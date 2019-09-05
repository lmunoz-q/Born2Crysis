/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_delete_button.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:26:55 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/05 12:37:45 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	delete_script(SDL_Event *event,
	t_libui_widget *widget,
	void *data)
{
	t_editor_interface	*edi;

	(void)event;
	(void)widget;
	widget = widget->parent;
	edi = (t_editor_interface *)data;
	if (widget == &edi->area_script_1)
	{
		get_world()->sectors[edi->secteur_courant].physics.entering_effet = -1;
		libui_label_set_text(&edi->label_script_1_file, SCRIPT_EMPTY);
	}
	if (widget == &edi->area_script_2)
	{
		get_world()->sectors[edi->secteur_courant].physics.leaving_effect = -1;
		libui_label_set_text(&edi->label_script_2_file, SCRIPT_EMPTY);
	}
	if (widget == &edi->area_script_3)
	{
		get_world()->sectors[edi->secteur_courant].physics.frame_effect = -1;
		libui_label_set_text(&edi->label_script_3_file, SCRIPT_EMPTY);
	}
	if (widget == &edi->area_script_obj)
	{
		libui_label_set_text(&edi->label_script_obj_file, SCRIPT_EMPTY);
		edi->item_placer->on_contact = -1;
	}
	return (0);
}

int			add_delete_button(t_libui_widgets_surface *ws,
			t_editor_interface *edi,
			t_libui_widget *area_script, t_libui_widget *button)
{
	t_libui_textbutton_constructor cons;

	libui_init_textbutton_constructor(&cons);
	cons = (t_libui_textbutton_constructor){ws,
		area_script, {90, 40, 20, 20}, {5, 0, 30,
		30}, "x", edi->font, cons.theme};
	if (libui_create_textbutton(button, &cons))
		return (1);
	libui_callback_setpressed(button,
		delete_script, SDL_MOUSEBUTTONDOWN, edi);
	return (0);
}
