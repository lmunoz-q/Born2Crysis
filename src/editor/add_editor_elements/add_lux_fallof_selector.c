/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lux_fallof_selector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:08:42 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/31 16:16:35 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

static int	add_l_f_s_sub1(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface,
	t_libui_textbutton_constructor *cons)
{
	cons->text = "-1";
	cons->ws = ws;
	if (libui_create_textbutton(
		&(editor_interface->lux_fallof_selec_down_button), cons))
	{
		printf("Error lors de la creation du textbouton -1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_fallof_selec_down_button),
		decrease_lux_fallof_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons->rect = (SDL_Rect){.x = 275, .y = 555, .w = 30, .h = 30};
	cons->text = "+1";
	if (libui_create_textbutton(&(editor_interface->lux_fallof_selec_up_button),
		cons))
	{
		printf("Error lors de la creation du textbouton +1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_fallof_selec_up_button),
		increase_lux_fallof_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	return (0);
}

static int	add_l_f_s_sub2(t_editor_interface *editor_interface,
	t_libui_textbutton_constructor *cons)
{
	cons->rect = (SDL_Rect){.x = 310, .y = 555, .w = 45, .h = 30};
	cons->text = "+0.1";
	if (libui_create_textbutton(
		&(editor_interface->lux_fallof_selec_up_dot1_button), cons))
	{
		printf("Error lors de la creation du textbouton +0.1.\n");
		return (1);
	}
	libui_callback_setpressed(
		&(editor_interface->lux_fallof_selec_up_dot1_button),
		increasedot1_lux_fallof_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons->rect = (SDL_Rect){.x = 10, .y = 555, .w = 35, .h = 30};
	cons->text = "-0.1";
	if (libui_create_textbutton(
		&(editor_interface->lux_fallof_selec_down_dot1_button), cons))
	{
		printf("Error lors de la creation du textbouton -0.1.\n");
		return (1);
	}
	libui_callback_setpressed(
		&(editor_interface->lux_fallof_selec_down_dot1_button),
		decreasedot1_lux_fallof_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	return (0);
}

int			add_lux_fallof_selector(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor cons;

	if (!libui_create_label(&(editor_interface->lux_fallof_selec_label),
		(SDL_Rect){.x = 80, .y = 560, .w = 195, .h = 20},
		"FallOf: 1", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->lux_fallof_selec_label), 0,
		&(editor_interface->editor_container));
	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 7, .y = 5, .w = 50, .h = 30};
	cons.rect = (SDL_Rect){.x = 50, .y = 555, .w = 30, .h = 30};
	if (add_l_f_s_sub1(ws, editor_interface, &cons))
		return (1);
	if (add_l_f_s_sub2(editor_interface, &cons))
		return (1);
	editor_interface->lux_fallof = 1.0;
	return (0);
}
