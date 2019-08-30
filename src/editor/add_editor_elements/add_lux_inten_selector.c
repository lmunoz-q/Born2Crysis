/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lux_inten_selector.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:02:31 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/30 14:10:40 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	add_l_i_s_sub1(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface,
	t_libui_textbutton_constructor *cons)
{
	cons->text = "-1";
	cons->ws = ws;
	if (libui_create_textbutton(
			&(editor_interface->lux_inten_selec_down_button), cons))
	{
		printf("Error lors de la creation du textbouton -1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_inten_selec_down_button),
		decrease_lux_inten_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons->rect = (SDL_Rect){.x = 275, .y = 515, .w = 30, .h = 30};
	cons->text = "+1";
	if (libui_create_textbutton(&(editor_interface->lux_inten_selec_up_button),
		cons))
	{
		printf("Error lors de la creation du textbouton +1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_inten_selec_up_button),
		increase_lux_inten_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	return (0);
}

static int	add_l_i_s_sub2(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface,
	t_libui_textbutton_constructor *cons)
{
	(void)ws;
	cons->rect = (SDL_Rect){.x = 310, .y = 515, .w = 45, .h = 30};
	cons->text = "+10";
	if (libui_create_textbutton(
		&(editor_interface->lux_inten_selec_up10_button), cons))
	{
		printf("Error lors de la creation du textbouton +10.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_inten_selec_up10_button),
		increase10_lux_inten_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons->rect = (SDL_Rect){.x = 10, .y = 515, .w = 35, .h = 30};
	cons->text = "-10";
	if (libui_create_textbutton(
		&(editor_interface->lux_inten_selec_down10_button), cons))
	{
		printf("Error lors de la creation du textbouton -10.\n");
		return (1);
	}
	libui_callback_setpressed(
		&(editor_interface->lux_inten_selec_down10_button),
		decrease10_lux_inten_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	return (0);
}

int			add_lux_inten_selector(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor cons;

	if (!libui_create_label(&(editor_interface->lux_inten_selec_label),
							(SDL_Rect){.x = 80, .y = 520, .w = 195, .h = 20},
							"Intensite: 1", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->lux_inten_selec_label), 0,
		&(editor_interface->editor_container));
	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 7, .y = 5, .w = 50, .h = 30};
	cons.rect = (SDL_Rect){.x = 50, .y = 515, .w = 30, .h = 30};
	if (add_l_i_s_sub1(ws, editor_interface, &cons))
		return (1);
	if (add_l_i_s_sub2(ws, editor_interface, &cons))
		return (1);
	editor_interface->lux_intensity = 1.0;
	return (0);
}
