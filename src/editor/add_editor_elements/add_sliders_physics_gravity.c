/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sliders_physics_gravity.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:24:36 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/30 14:15:20 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	add_s_p_g_sub1(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	static struct s_double_value_slider dvs_x;

	(void)ws;
	if (!libui_create_slider(&editor_interface->slider_physics_gravity_x,
		(SDL_Rect){20, 700, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_gravity_x, -500, 500);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_gravity_x, 0);
	if (!libui_create_label(&editor_interface->label_physics_gravity_x,
		(SDL_Rect){2, 700, 16, 20}, "x:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_gravity_x,
		(SDL_Rect){122, 700, 40, 20}, "0", editor_interface->font))
		return (-1);
	dvs_x.value = &(editor_interface->sector_gravity.n.x);
	dvs_x.label = &editor_interface->labelNB_physics_gravity_x;
	libui_callback_setpressed(&editor_interface->slider_physics_gravity_x,
		slider_on_press_label_update, SDL_MOUSEBUTTONDOWN, &dvs_x);
	return (0);
}

static int	add_s_p_g_sub2(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	static struct s_double_value_slider dvs_y;

	(void)ws;
	if (!libui_create_slider(&editor_interface->slider_physics_gravity_y,
		(SDL_Rect){20, 722, 100, 20}, SDL_FALSE))
		return (1);
	dvs_y.value = &(editor_interface->sector_gravity.n.y);
	dvs_y.label = &editor_interface->labelNB_physics_gravity_y;
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_gravity_y, -500, 500);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_gravity_y, 0);
	if (!libui_create_label(&editor_interface->label_physics_gravity_y,
		(SDL_Rect){2, 722, 16, 20}, "y:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_gravity_y,
		(SDL_Rect){122, 722, 40, 20}, "0", editor_interface->font))
		return (-1);
	libui_callback_setpressed(&editor_interface->slider_physics_gravity_y,
	slider_on_press_label_update, SDL_MOUSEBUTTONDOWN, &dvs_y);
	return (0);
}

static int	add_s_p_g_sub3(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	static struct s_double_value_slider dvs_z;

	(void)ws;
	if (!libui_create_slider(&editor_interface->slider_physics_gravity_z,
		(SDL_Rect){20, 744, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_gravity_z, -500, 500);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_gravity_z, 0);
	if (!libui_create_label(&editor_interface->label_physics_gravity_z,
		(SDL_Rect){2, 744, 16, 20}, "z:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_gravity_z,
		(SDL_Rect){122, 744, 40, 20}, "0", editor_interface->font))
		return (-1);
	dvs_z.value = &(editor_interface->sector_gravity.n.z);
	dvs_z.label = &editor_interface->labelNB_physics_gravity_z;
	libui_callback_setpressed(&editor_interface->slider_physics_gravity_z,
		slider_on_press_label_update, SDL_MOUSEBUTTONDOWN, &dvs_z);
	return (0);
}

static void	add_s_p_g_sub4(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	(void)ws;
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gravity_x,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_gravity_x,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_gravity_x, 0,
		&editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gravity_y, 0,
		&editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_gravity_y,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_gravity_y, 0,
		&editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gravity_z, 0,
		&editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_gravity_z,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_gravity_z, 0,
		&editor_interface->editor_container);
}

int			add_sliders_physics_gravity(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	(void)ws;
	if (!libui_create_label(&editor_interface->label_physics_gravity,
		(SDL_Rect){2, 678, 160, 20}, "Gravity", editor_interface->font))
		return (-1);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gravity, 0,
		&editor_interface->editor_container);
	if (add_s_p_g_sub1(ws, editor_interface))
		return (1);
	if (add_s_p_g_sub2(ws, editor_interface))
		return (1);
	if (add_s_p_g_sub3(ws, editor_interface))
		return (1);
	add_s_p_g_sub4(ws, editor_interface);
	update_double_slider_data(&editor_interface->slider_physics_gravity_x,
		&editor_interface->labelNB_physics_gravity_x,
		editor_interface->sector_gravity.n.x);
	update_double_slider_data(&editor_interface->slider_physics_gravity_y,
		&editor_interface->labelNB_physics_gravity_y,
		editor_interface->sector_gravity.n.y);
	update_double_slider_data(&editor_interface->slider_physics_gravity_z,
		&editor_interface->labelNB_physics_gravity_z,
		editor_interface->sector_gravity.n.z);
	return (0);
}
