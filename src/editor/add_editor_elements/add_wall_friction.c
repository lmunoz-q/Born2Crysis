/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_wall_friction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:22:49 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/01 18:13:17 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	update_wf_type_text(t_libui_widget *widget,
	SDL_bool is_auto)
{
	char	new_text[BASE_TEXT_SIZE + 1];

	doom_clean_text(new_text, BASE_TEXT_SIZE);
	if (is_auto)
		doom_fill_text(new_text, WALL_FRICTION_AUTO_TEXT, FRICTION_TYPE_TEXT);
	else
		doom_fill_text(new_text, WALL_FRICTION_MAN_TEXT, FRICTION_TYPE_TEXT);
	libui_label_set_text(widget, new_text);
}

int			toggle_friction_mode(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	t_editor_interface	*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->wall_friction_is_auto)
		editor_interface->wall_friction_is_auto = SDL_FALSE;
	else
		editor_interface->wall_friction_is_auto = SDL_TRUE;
	update_wf_type_text(editor_interface->button_wall_friction.shilds,
		editor_interface->wall_friction_is_auto);
	return (0);
}

static void	add_wall_friction_sub(
	t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	libui_widgets_add_widget(ws, &editor_interface->
		slider_physics_wall_friction, 0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->
		label_nb_physics_wall_friction, 0, &editor_interface->editor_container);
	update_wf_type_text(editor_interface->button_wall_friction.shilds,
		editor_interface->wall_friction_is_auto);
	libui_progressbar_set_current_value(&editor_interface->
		slider_physics_wall_friction, 0);
}

int			add_wall_friction(
	t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor		cons;
	static struct s_double_value_slider	dvs_wf;

	libui_init_textbutton_constructor(&cons);
	cons = (t_libui_textbutton_constructor){ws,
		&editor_interface->editor_container, {290, 790, 200, 20}, {5, 2, 200,
		50}, "Friction : auto", editor_interface->font, cons.theme};
	if (libui_create_textbutton(&(editor_interface->
		button_wall_friction), &cons))
		return (1);
	libui_callback_setpressed(&editor_interface->button_wall_friction,
		toggle_friction_mode, SDL_MOUSEBUTTONDOWN, editor_interface);
	if (!libui_create_slider(&editor_interface->slider_physics_wall_friction,
		(SDL_Rect){290, 812, 158, 20}, SDL_FALSE))
		return (1);
	if (!libui_create_label(&editor_interface->label_nb_physics_wall_friction,
		(SDL_Rect){450, 812, 40, 20}, "0", editor_interface->font))
		return (-1);
	dvs_wf.value = &(editor_interface->wall_friction);
	dvs_wf.label = &editor_interface->label_nb_physics_wall_friction;
	libui_callback_setpressed(&editor_interface->slider_physics_wall_friction,
		slider_on_press_label_update, SDL_MOUSEBUTTONDOWN, &dvs_wf);
	add_wall_friction_sub(ws, editor_interface);
	return (0);
}
