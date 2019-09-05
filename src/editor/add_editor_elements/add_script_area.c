/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_script_area.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:32:01 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/05 11:42:25 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	func_void(SDL_Event *event,
	t_libui_widget *widget,
	void *data)
{
	(void)event;
	(void)widget;
	(void)data;
	return (0);
}

static int	create_script_1_area(t_libui_widgets_surface *ws,
	t_editor_interface *edi)
{
	edi->script_1_area = (SDL_Rect){160, 980, 110, 100};
	if (!libui_create_container(&edi->area_script_1,
		edi->script_1_area, 0xffaaaaaa))
		return (-1);
	edi->script_1_area.x = 0;
	edi->script_1_area.y = 0;
	edi->script_1_area.h = 20;
	if (!libui_create_label(&edi->label_script_1_aim, edi->script_1_area,
		SCRIPT_1_AIM, edi->font))
		return (-1);
	edi->script_1_area.y = 70;
	if (!libui_create_label(&edi->label_script_1_file, edi->script_1_area,
		SCRIPT_EMPTY, edi->font))
		return (-1);
	libui_callback_sethover(&edi->area_script_1, func_void,
		SDL_MOUSEMOTION, NULL);
	libui_widgets_add_widget(ws, &edi->area_script_1, 0,
		&edi->editor_container);
	libui_widgets_add_widget(ws, &edi->label_script_1_aim, 0,
		&edi->area_script_1);
	libui_widgets_add_widget(ws, &edi->label_script_1_file, 0,
		&edi->area_script_1);
	edi->script_1_area = edi->area_script_1.rect;
	return (add_delete_button(ws, edi, &edi->area_script_1, &edi->button_disconnect_script_1));
}

static int	create_script_2_area(t_libui_widgets_surface *ws,
	t_editor_interface *edi)
{
	edi->script_2_area = (SDL_Rect){275, 980, 110, 100};
	if (!libui_create_container(&edi->area_script_2,
		edi->script_2_area, 0xffaaaaaa))
		return (-1);
	edi->script_2_area.x = 0;
	edi->script_2_area.y = 0;
	edi->script_2_area.h = 20;
	if (!libui_create_label(&edi->label_script_2_aim, edi->script_2_area,
		SCRIPT_2_AIM, edi->font))
		return (-1);
	edi->script_2_area.y = 70;
	if (!libui_create_label(&edi->label_script_2_file, edi->script_2_area,
		SCRIPT_EMPTY, edi->font))
		return (-1);
	libui_callback_sethover(&edi->area_script_2, func_void,
		SDL_MOUSEMOTION, NULL);
	libui_widgets_add_widget(ws, &edi->area_script_2, 0,
		&edi->editor_container);
	libui_widgets_add_widget(ws, &edi->label_script_2_aim, 0,
		&edi->area_script_2);
	libui_widgets_add_widget(ws, &edi->label_script_2_file, 0,
		&edi->area_script_2);
	edi->script_2_area = edi->area_script_2.rect;
	return (add_delete_button(ws, edi, &edi->area_script_2, &edi->button_disconnect_script_2));
}

static int	create_script_3_area(t_libui_widgets_surface *ws,
	t_editor_interface *edi)
{
	edi->script_3_area = (SDL_Rect){390, 980, 110, 100};
	if (!libui_create_container(&edi->area_script_3,
		edi->script_3_area, 0xffaaaaaa))
		return (-1);
	edi->script_3_area.x = 0;
	edi->script_3_area.y = 0;
	edi->script_3_area.h = 20;
	if (!libui_create_label(&edi->label_script_3_aim, edi->script_3_area,
		SCRIPT_3_AIM, edi->font))
		return (-1);
	edi->script_3_area.y = 70;
	if (!libui_create_label(&edi->label_script_3_file, edi->script_3_area,
		SCRIPT_EMPTY, edi->font))
		return (-1);
	libui_callback_sethover(&edi->area_script_3, func_void,
		SDL_MOUSEMOTION, NULL);
	libui_widgets_add_widget(ws, &edi->area_script_3, 0,
		&edi->editor_container);
	libui_widgets_add_widget(ws, &edi->label_script_3_aim, 0,
		&edi->area_script_3);
	libui_widgets_add_widget(ws, &edi->label_script_3_file, 0,
		&edi->area_script_3);
	edi->script_3_area = edi->area_script_3.rect;
	return (add_delete_button(ws, edi, &edi->area_script_3, &edi->button_disconnect_script_3));
}

int			add_script_area(t_libui_widgets_surface *ws,
	t_editor_interface *edi)
{
	doom_str_clean(edi->script_1_name, 12);
	doom_str_clean(edi->script_2_name, 12);
	doom_str_clean(edi->script_3_name, 12);
	if (create_script_1_area(ws, edi))
		return (-1);
	if (create_script_2_area(ws, edi))
		return (-1);
	if (create_script_3_area(ws, edi))
		return (-1);
	if (create_script_obj_area(ws, edi))
		return (-1);
	return (0);
}
