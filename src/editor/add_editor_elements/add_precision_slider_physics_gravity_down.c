/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_precision_slider_physics_gravity_down.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 21:49:51 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/01 00:37:09 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	decrease_dot01_gravity_x(SDL_Event *event,
	t_libui_widget *widget,
	void *data)
{
	double						tmp_x;
	char						tmp_text[25];
	t_editor_interface			*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->sector_gravity.n.x > -5.0)
		editor_interface->sector_gravity.n.x -= 0.01;
	if (editor_interface->sector_gravity.n.x < -5.0)
		editor_interface->sector_gravity.n.x = -5.0;
	tmp_x = editor_interface->sector_gravity.n.x;
	doom_str_clean(tmp_text, 25);
	libui_progressbar_set_current_value(&editor_interface->
		slider_physics_gravity_x, (int)(tmp_x * 100));
	doom_dtoa(tmp_x, tmp_text, 25);
	libui_label_set_text(&editor_interface->label_nb_physics_gravity_x,
		tmp_text);
	return (0);
}

static int	decrease_dot01_gravity_y(SDL_Event *event,
	t_libui_widget *widget,
	void *data)
{
	double						tmp_x;
	char						tmp_text[25];
	t_editor_interface			*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->sector_gravity.n.y > -5.0)
		editor_interface->sector_gravity.n.y -= 0.01;
	if (editor_interface->sector_gravity.n.y < -5.0)
		editor_interface->sector_gravity.n.y = -5.0;
	tmp_x = editor_interface->sector_gravity.n.y;
	doom_str_clean(tmp_text, 25);
	libui_progressbar_set_current_value(&editor_interface->
		slider_physics_gravity_y, (int)(tmp_x * 100));
	doom_dtoa(tmp_x, tmp_text, 25);
	libui_label_set_text(&editor_interface->label_nb_physics_gravity_y,
		tmp_text);
	return (0);
}

static int	decrease_dot01_gravity_z(SDL_Event *event,
	t_libui_widget *widget,
	void *data)
{
	double						tmp_x;
	char						tmp_text[25];
	t_editor_interface			*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->sector_gravity.n.z > -5.0)
		editor_interface->sector_gravity.n.z -= 0.01;
	if (editor_interface->sector_gravity.n.z < -5.0)
		editor_interface->sector_gravity.n.z = -5.0;
	tmp_x = editor_interface->sector_gravity.n.z;
	doom_str_clean(tmp_text, 25);
	libui_progressbar_set_current_value(&editor_interface->
		slider_physics_gravity_z, (int)(tmp_x * 100));
	doom_dtoa(tmp_x, tmp_text, 25);
	libui_label_set_text(&editor_interface->label_nb_physics_gravity_z,
		tmp_text);
	return (0);
}

int			add_precision_slider_physics_gravity_down(
	t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor cons;

	libui_init_textbutton_constructor(&cons);
	cons = (t_libui_textbutton_constructor){ws,
		&editor_interface->editor_container, {165, 700, 50, 20}, {5, 2, 50,
		50}, "-0.01", editor_interface->font, cons.theme};
	if (libui_create_textbutton(&(editor_interface->
		down_button_physics_gravity_x), &cons))
		return (1);
	libui_callback_setpressed(&(editor_interface->down_button_physics_gravity_x),
		decrease_dot01_gravity_x, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons.rect = (SDL_Rect){.x = 165, .y = 722, .w = 50, .h = 20};
	if (libui_create_textbutton(&(editor_interface->
		down_button_physics_gravity_y), &cons))
		return (1);
	libui_callback_setpressed(&(editor_interface->down_button_physics_gravity_y),
		decrease_dot01_gravity_y, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons.rect = (SDL_Rect){.x = 165, .y = 744, .w = 50, .h = 20};
	if (libui_create_textbutton(&(editor_interface->
		down_button_physics_gravity_z), &cons))
		return (1);
	libui_callback_setpressed(&(editor_interface->down_button_physics_gravity_z),
		decrease_dot01_gravity_z, SDL_MOUSEBUTTONDOWN, editor_interface);
	return (0);
}
