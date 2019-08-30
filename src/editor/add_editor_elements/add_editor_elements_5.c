/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_editor_elements_5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:39:03 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/30 16:39:06 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

static int	add_secteur2_selector_sub(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface, t_e *e,
	t_libui_textbutton_constructor *cons)
{
	(void)ws;
	if (libui_create_textbutton(&(editor_interface->secteur2_selec_down_button),
								cons))
	{
		printf("Error lors de la creation du textbouton -1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->secteur2_selec_down_button),
		decrease_secteur2_number, SDL_MOUSEBUTTONDOWN,
		editor_interface);
	cons->rect = (SDL_Rect){.x = 235, .y = 360, .w = 30, .h = 30};
	cons->text = "+1";
	if (libui_create_textbutton(&(editor_interface->secteur2_selec_up_button),
		cons))
	{
		printf("Error lors de la creation du textbouton +1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->secteur2_selec_up_button),
		increase_secteur2_number, SDL_MOUSEBUTTONDOWN, e);
	return (0);
}

int			add_secteur2_selector(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface, t_e *e)
{
	t_libui_textbutton_constructor cons;

	if (!libui_create_label(&(editor_interface->secteur2_selec_label),
		(SDL_Rect){.x = 40, .y = 365, .w = 195, .h = 20},
		"Secteur secondaire: 0", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->secteur2_selec_label), 0,
		&(editor_interface->editor_container));
	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 8, .y = 5, .w = 30, .h = 30};
	cons.rect = (SDL_Rect){.x = 10, .y = 360, .w = 30, .h = 30};
	cons.text = "-1";
	cons.ws = ws;
	if (add_secteur2_selector_sub(ws, editor_interface, e, &cons))
		return (1);
	editor_interface->secteur2_courant = 0;
	return (0);
}
