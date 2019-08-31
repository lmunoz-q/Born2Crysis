/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_slider_alpha.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:47:50 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/31 15:43:49 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

static int	add_s_a_sub(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	static struct s_int_value_slider ivs_a;

	if (!libui_create_label(&editor_interface->slider_title_alpha,
		(SDL_Rect){165, 678, 160, 20}, "Alpha", editor_interface->font))
		return (-1);
	libui_widgets_add_widget(ws, &editor_interface->slider_title_alpha, 0,
		&editor_interface->editor_container);
	if (!libui_create_slider(&editor_interface->slider_alpha,
		(SDL_Rect){183, 700, 275, 20}, SDL_FALSE))
		return (-1);
	libui_progressbar_set_minmax_value(&editor_interface->slider_alpha, 0, 255);
	libui_progressbar_set_current_value(&editor_interface->slider_alpha, 0);
	if (!libui_create_label(&editor_interface->label_alpha,
		(SDL_Rect){165, 700, 16, 20}, "a:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->label_nb_alpha,
		(SDL_Rect){460, 700, 40, 20}, "0", editor_interface->font))
		return (-1);
	ivs_a.value = &(editor_interface->alpha);
	ivs_a.label = &editor_interface->label_nb_alpha;
	libui_callback_setpressed(&editor_interface->slider_alpha,
		slider_on_press_label_update2, SDL_MOUSEBUTTONDOWN, &ivs_a);
	return (0);
}

int			add_slider_alpha(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	if (add_s_a_sub(ws, editor_interface))
		return (1);
	libui_widgets_add_widget(ws, &editor_interface->label_alpha, 0,
		&editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->label_nb_alpha,
		0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_alpha, 0,
		&editor_interface->editor_container);
	return (0);
}
