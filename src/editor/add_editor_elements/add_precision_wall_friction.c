/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_precision_wall_friction.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 18:01:04 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/01 18:11:40 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	decrease_dot01_wall_friction(SDL_Event *event,
	t_libui_widget *widget,
	void *data)
{
	double						tmp_x;
	char						tmp_text[25];
	t_editor_interface			*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->wall_friction > 0.0)
		editor_interface->wall_friction -= 0.01;
	if (editor_interface->wall_friction < 0.0)
		editor_interface->wall_friction = 0.0;
	tmp_x = editor_interface->wall_friction;
	doom_str_clean(tmp_text, 25);
	libui_progressbar_set_current_value(&editor_interface->
		slider_physics_wall_friction, (int)(tmp_x * 100));
	doom_dtoa(tmp_x, tmp_text, 25);
	libui_label_set_text(&editor_interface->label_nb_physics_wall_friction,
		tmp_text);
	return (0);
}

static int	increase_dot01_wall_friction(SDL_Event *event,
	t_libui_widget *widget,
	void *data)
{
	double						tmp_x;
	char						tmp_text[25];
	t_editor_interface			*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->wall_friction < 1.0)
		editor_interface->wall_friction += 0.01;
	if (editor_interface->wall_friction > 1.0)
		editor_interface->wall_friction = 1.0;
	tmp_x = editor_interface->wall_friction;
	doom_str_clean(tmp_text, 25);
	libui_progressbar_set_current_value(&editor_interface->
		slider_physics_wall_friction, (int)(tmp_x * 100));
	doom_dtoa(tmp_x, tmp_text, 25);
	libui_label_set_text(&editor_interface->label_nb_physics_wall_friction,
		tmp_text);
	return (0);
}

int			add_precision_wall_friction(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor cons;

	libui_init_textbutton_constructor(&cons);
	cons = (t_libui_textbutton_constructor){ws,
		&editor_interface->editor_container, {290, 834, 50, 20}, {5, 2, 50,
		50}, "-0.01", editor_interface->font, cons.theme};
	if (libui_create_textbutton(&(editor_interface->
		down_button_physics_wall_f), &cons))
		return (1);
	libui_callback_setpressed(&editor_interface->down_button_physics_wall_f,
		decrease_dot01_wall_friction, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons.rect = (SDL_Rect){.x = 440, .y = 834, .w = 50, .h = 20};
	if (libui_create_textbutton(&(editor_interface->up_button_physics_wall_f),
		&cons))
		return (1);
	libui_callback_setpressed(&editor_interface->up_button_physics_wall_f,
		increase_dot01_wall_friction, SDL_MOUSEBUTTONDOWN, editor_interface);
	return (0);
}
