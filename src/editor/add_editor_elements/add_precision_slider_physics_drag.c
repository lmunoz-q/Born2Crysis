/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_precision_slider_physics_drag.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 00:00:52 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/01 00:26:50 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	increase_dot01_drag_x(SDL_Event *event,
	t_libui_widget *widget,
	void *data)
{
	double						tmp_x;
	char						tmp_text[25];
	t_editor_interface			*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->sector_drag.n.x < 1.0)
		editor_interface->sector_drag.n.x += 0.01;
	if (editor_interface->sector_drag.n.x > 1.0)
		editor_interface->sector_drag.n.x = 1.0;
	tmp_x = editor_interface->sector_drag.n.x;
	doom_str_clean(tmp_text, 25);
	libui_progressbar_set_current_value(&editor_interface->
		slider_physics_drag_x, (int)(tmp_x * 100));
	doom_dtoa(tmp_x, tmp_text, 25);
	libui_label_set_text(&editor_interface->label_nb_physics_drag_x,
		tmp_text);
	return (0);
}

static int	increase_dot01_drag_y(SDL_Event *event,
	t_libui_widget *widget,
	void *data)
{
	double						tmp_x;
	char						tmp_text[25];
	t_editor_interface			*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->sector_drag.n.y < 1.0)
		editor_interface->sector_drag.n.y += 0.01;
	if (editor_interface->sector_drag.n.y > 1.0)
		editor_interface->sector_drag.n.y = 1.0;
	tmp_x = editor_interface->sector_drag.n.y;
	doom_str_clean(tmp_text, 25);
	libui_progressbar_set_current_value(&editor_interface->
		slider_physics_drag_y, (int)(tmp_x * 100));
	doom_dtoa(tmp_x, tmp_text, 25);
	libui_label_set_text(&editor_interface->label_nb_physics_drag_y,
		tmp_text);
	return (0);
}

static int	increase_dot01_drag_z(SDL_Event *event,
	t_libui_widget *widget,
	void *data)
{
	double						tmp_x;
	char						tmp_text[25];
	t_editor_interface			*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->sector_drag.n.z < 1.0)
		editor_interface->sector_drag.n.z += 0.01;
	if (editor_interface->sector_drag.n.z > 1.0)
		editor_interface->sector_drag.n.z = 1.0;
	tmp_x = editor_interface->sector_drag.n.z;
	doom_str_clean(tmp_text, 25);
	libui_progressbar_set_current_value(&editor_interface->
		slider_physics_drag_z, (int)(tmp_x * 100));
	doom_dtoa(tmp_x, tmp_text, 25);
	libui_label_set_text(&editor_interface->label_nb_physics_drag_z,
		tmp_text);
	return (0);
}

int			add_precision_slider_physics_drag_up(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor cons;

	libui_init_textbutton_constructor(&cons);
	cons = (t_libui_textbutton_constructor){ws,
		&editor_interface->editor_container, {220, 880, 50, 20}, {5, 2, 50,
		50}, "+0.01", editor_interface->font, cons.theme};
	if (libui_create_textbutton(&(editor_interface->
		up_button_physics_drag_x), &cons))
		return (1);
	libui_callback_setpressed(&(editor_interface->up_button_physics_drag_x),
		increase_dot01_drag_x, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons.rect = (SDL_Rect){.x = 220, .y = 902, .w = 50, .h = 20};
	if (libui_create_textbutton(&(editor_interface->
		up_button_physics_drag_y), &cons))
		return (1);
	libui_callback_setpressed(&(editor_interface->up_button_physics_drag_y),
		increase_dot01_drag_y, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons.rect = (SDL_Rect){.x = 220, .y = 924, .w = 50, .h = 20};
	if (libui_create_textbutton(&(editor_interface->
		up_button_physics_drag_z), &cons))
		return (1);
	libui_callback_setpressed(&(editor_interface->up_button_physics_drag_z),
		increase_dot01_drag_z, SDL_MOUSEBUTTONDOWN, editor_interface);
	return (0);
}
