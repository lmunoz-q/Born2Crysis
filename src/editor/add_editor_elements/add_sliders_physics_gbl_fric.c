/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sliders_physics_gbl_fric.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:34:06 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/30 13:40:29 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	add_s_p_g_f_sub1(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	static struct s_double_value_slider dvs_x;

	if (!libui_create_slider(&editor_interface->slider_physics_gbl_fric_x,
		(SDL_Rect){20, 790, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_gbl_fric_x, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_gbl_fric_x, 0);
	if (!libui_create_label(&editor_interface->label_physics_gbl_fric_x,
		(SDL_Rect){2, 790, 16, 20}, "x:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_gbl_fric_x,
		(SDL_Rect){122, 790, 40, 20}, "0", editor_interface->font))
		return (-1);
	dvs_x.value = &(editor_interface->sector_global_friction.n.x);
	dvs_x.label = &editor_interface->labelNB_physics_gbl_fric_x;
	libui_callback_setpressed(&editor_interface->slider_physics_gbl_fric_x,
		slider_on_pressLabelUpdate, SDL_MOUSEBUTTONDOWN, &dvs_x);
	return (0);
}

static int	add_s_p_g_f_sub2(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	static struct s_double_value_slider dvs_y;

	if (!libui_create_slider(&editor_interface->slider_physics_gbl_fric_y,
		(SDL_Rect){20, 812, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_gbl_fric_y, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_gbl_fric_y, 0);
	if (!libui_create_label(&editor_interface->label_physics_gbl_fric_y,
		(SDL_Rect){2, 812, 16, 20}, "y:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_gbl_fric_y,
		(SDL_Rect){122, 812, 40, 20}, "0", editor_interface->font))
		return (-1);
	dvs_y.value = &(editor_interface->sector_global_friction.n.y);
	dvs_y.label = &editor_interface->labelNB_physics_gbl_fric_y;
	libui_callback_setpressed(&editor_interface->slider_physics_gbl_fric_y,
		slider_on_pressLabelUpdate, SDL_MOUSEBUTTONDOWN, &dvs_y);
	return (0);
}

static int	add_s_p_g_f_sub3(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	static struct s_double_value_slider dvs_z;

	if (!libui_create_slider(&editor_interface->slider_physics_gbl_fric_z,
		(SDL_Rect){20, 834, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_gbl_fric_z, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_gbl_fric_z, 0);
	if (!libui_create_label(&editor_interface->label_physics_gbl_fric_z,
		(SDL_Rect){2, 834, 16, 20}, "z:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_gbl_fric_z,
		(SDL_Rect){122, 834, 40, 20}, "0", editor_interface->font))
		return (-1);
	dvs_z.value = &(editor_interface->sector_global_friction.n.z);
	dvs_z.label = &editor_interface->labelNB_physics_gbl_fric_z;
	libui_callback_setpressed(&editor_interface->slider_physics_gbl_fric_z,
		slider_on_pressLabelUpdate, SDL_MOUSEBUTTONDOWN, &dvs_z);
	return (0);
}

static void	add_s_p_g_f_sub4(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gbl_fric_x, 0,
		&editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_gbl_fric_x,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_gbl_fric_x,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gbl_fric_y, 0,
		&editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_gbl_fric_y,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_gbl_fric_y,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gbl_fric_z, 0,
		&editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_gbl_fric_z,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_gbl_fric_z,
		0, &editor_interface->editor_container);
}

int			add_sliders_physics_gbl_fric(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{

	if (!libui_create_label(&editor_interface->label_physics_gbl_fric,
		(SDL_Rect){2, 768, 160, 20}, "Global Friction", editor_interface->font))
		return (-1);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gbl_fric, 0,
		&editor_interface->editor_container);
	if (add_s_p_g_f_sub1(ws, editor_interface))
		return (1);
	if (add_s_p_g_f_sub2(ws, editor_interface))
		return (1);
	if (add_s_p_g_f_sub3(ws, editor_interface))
		return (1);
	add_s_p_g_f_sub4(ws, editor_interface)
	update_double_slider_data(&editor_interface->slider_physics_gbl_fric_x,
		&editor_interface->labelNB_physics_gbl_fric_x,
			editor_interface->sector_global_friction.n.x);
	update_double_slider_data(&editor_interface->slider_physics_gbl_fric_y,
		&editor_interface->labelNB_physics_gbl_fric_y,
		editor_interface->sector_global_friction.n.y);
	update_double_slider_data(&editor_interface->slider_physics_gbl_fric_z,
		&editor_interface->labelNB_physics_gbl_fric_z,
		editor_interface->sector_global_friction.n.z);
	return (0);
}
