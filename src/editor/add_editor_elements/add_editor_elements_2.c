/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_editor_elements_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 12:46:09 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/31 16:07:36 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

static int	add_basic_entity_choice_sub1(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface,
	t_libui_textbutton_constructor *cons)
{
	libui_init_textbutton_constructor(cons);
	cons->parent = &(editor_interface->editor_container);
	cons->font = editor_interface->font;
	cons->label_rect = (SDL_Rect){.x = 10, .y = 10, .w = 100, .h = 50};
	cons->rect = (SDL_Rect)
		{.x = 10, .y = 415, .w = 150, .h = 50};
	cons->text = "LIGHT (OFF)";
	cons->ws = ws;
	if (libui_create_textbutton(&(editor_interface->light_textbutton), cons))
	{
		printf("Error lors de la creation du textbouton Wall.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->light_textbutton),
		bf_switch_light, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons->rect = (SDL_Rect)
		{.x = EDITOR_MENU_WIDTH - 80, .y = 260, .w = 80, .h = 50};
	cons->text = "SKYBOX";
	if (libui_create_textbutton(&(editor_interface->skybox_textbutton), cons))
	{
		printf("Error lors de la creation du textbouton Obj.\n");
		return (1);
	}
	return (0);
}

static int	add_basic_entity_choice_sub2(t_editor_interface *editor_interface,
	t_e *e, t_libui_textbutton_constructor *cons)
{
	libui_callback_setpressed(&(editor_interface->skybox_textbutton),
		bf_set_skybox, SDL_MOUSEBUTTONDOWN, e);
	cons->rect = (SDL_Rect)
		{.x = EDITOR_MENU_WIDTH - 80, .y = 320, .w = 80, .h = 50};
	cons->text = "MESH";
	editor_interface->is_making_portail = FALSE;
	if (libui_create_textbutton(&(editor_interface->portail_textbutton), cons))
	{
		printf("Error lors de la creation du textbouton Port.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->portail_textbutton),
		portail_pressed, SDL_MOUSEBUTTONDOWN, editor_interface);
	return (0);
}

int			add_basic_entity_choice(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface, t_e *e)
{
	t_libui_textbutton_constructor cons;

	if (add_basic_entity_choice_sub1(ws, editor_interface, &cons))
		return (1);
	if (add_basic_entity_choice_sub2(editor_interface, e, &cons))
		return (1);
	cons.rect = (SDL_Rect)
		{.x = EDITOR_MENU_WIDTH - 80, .y = 200, .w = 80, .h = 50};
	cons.text = "GOAL";
	editor_interface->is_making_portail = FALSE;
	if (libui_create_textbutton(&(editor_interface->goal_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Port.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->goal_textbutton),
		bf_switch_goal, SDL_MOUSEBUTTONDOWN, editor_interface);
	return (0);
}
