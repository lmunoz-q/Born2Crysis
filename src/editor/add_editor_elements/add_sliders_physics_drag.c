/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sliders_physics_drag.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:41:04 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/30 14:13:20 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

static int	add_s_p_d_sub1(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	(void)ws;
	static struct s_double_value_slider dvs_x;

	if (!libui_create_slider(&editor_interface->slider_physics_drag_x,
		(SDL_Rect){20, 880, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_drag_x, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_drag_x, 0);
	if (!libui_create_label(&editor_interface->label_physics_drag_x,
		(SDL_Rect){2, 880, 16, 20}, "x:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->label_nb_physics_drag_x,
		(SDL_Rect){122, 880, 40, 20}, "0", editor_interface->font))
		return (-1);
	dvs_x.value = &(editor_interface->sector_global_friction.n.x);
	dvs_x.label = &editor_interface->label_nb_physics_drag_x;
	libui_callback_setpressed(&editor_interface->slider_physics_drag_x,
	slider_on_press_label_update, SDL_MOUSEBUTTONDOWN, &dvs_x);
	return (0);
}

static int	add_s_p_d_sub2(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	static struct s_double_value_slider dvs_y;

	(void)ws;
	if (!libui_create_slider(&editor_interface->slider_physics_drag_y,
		(SDL_Rect){20, 902, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_drag_y, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_drag_y, 0);
	if (!libui_create_label(&editor_interface->label_physics_drag_y,
		(SDL_Rect){2, 902, 16, 20}, "y:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->label_nb_physics_drag_y,
		(SDL_Rect){122, 902, 40, 20}, "0", editor_interface->font))
		return (-1);
	dvs_y.value = &(editor_interface->sector_global_friction.n.y);
	dvs_y.label = &editor_interface->label_nb_physics_drag_y;
	libui_callback_setpressed(&editor_interface->slider_physics_drag_y,
		slider_on_press_label_update, SDL_MOUSEBUTTONDOWN, &dvs_y);
	return (0);
}

static int	add_s_p_d_sub3(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	static struct s_double_value_slider dvs_z;

	(void)ws;
	if (!libui_create_slider(&editor_interface->slider_physics_drag_z,
		(SDL_Rect){20, 924, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_drag_z, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_drag_z, 0);
	if (!libui_create_label(&editor_interface->label_physics_drag_z,
		(SDL_Rect){2, 924, 16, 20}, "z:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->label_nb_physics_drag_z,
		(SDL_Rect){122, 924, 40, 20}, "0", editor_interface->font))
		return (-1);
	dvs_z.value = &(editor_interface->sector_global_friction.n.z);
	dvs_z.label = &editor_interface->label_nb_physics_drag_z;
	libui_callback_setpressed(&editor_interface->slider_physics_drag_z,
		slider_on_press_label_update, SDL_MOUSEBUTTONDOWN, &dvs_z);
	return (0);
}

static void	add_s_p_d_sub4(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	libui_widgets_add_widget(ws, &editor_interface->label_physics_drag_x, 0,
		&editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->label_nb_physics_drag_x,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_drag_x,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_drag_y, 0,
		&editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->label_nb_physics_drag_y,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_drag_y,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_drag_z, 0,
		&editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->label_nb_physics_drag_z,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_drag_z,
		0, &editor_interface->editor_container);
}

int			add_sliders_physics_drag(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{

	(void)ws;
	if (!libui_create_label(&editor_interface->label_physics_drag,
		(SDL_Rect){2, 858, 160, 20}, "Drag", editor_interface->font))
		return (-1);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_drag, 0,
		&editor_interface->editor_container);
	if (add_s_p_d_sub1(ws, editor_interface))
		return (1);
	if (add_s_p_d_sub2(ws, editor_interface))
		return (1);
	if (add_s_p_d_sub3(ws, editor_interface))
		return (1);
	add_s_p_d_sub4(ws, editor_interface);
	update_double_slider_data(&editor_interface->slider_physics_drag_x,
	&editor_interface->label_nb_physics_drag_x,
	editor_interface->sector_drag.n.x);
	update_double_slider_data(&editor_interface->slider_physics_drag_y,
	&editor_interface->label_nb_physics_drag_y,
	editor_interface->sector_drag.n.y);
	update_double_slider_data(&editor_interface->slider_physics_drag_z,
	&editor_interface->label_nb_physics_drag_z,
	editor_interface->sector_drag.n.z);
	return (0);
}
