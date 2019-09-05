/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_script_obj_area.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:20:27 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/05 11:42:51 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int		func_void2(SDL_Event *event,
	t_libui_widget *widget,
	void *data)
{
	(void)event;
	(void)widget;
	(void)data;
	return (0);
}

int				create_script_obj_area(t_libui_widgets_surface *ws,
						t_editor_interface *edi)
{
	edi->script_obj_area = (SDL_Rect){390, 870, 110, 100};
	if (!libui_create_container(&edi->area_script_obj,
		edi->script_obj_area, 0xffaaaaaa))
		return (-1);
	edi->script_obj_area.x = 0;
	edi->script_obj_area.y = 0;
	edi->script_obj_area.h = 20;
	if (!libui_create_label(&edi->label_script_obj_aim, edi->script_obj_area,
		SCRIPT_OBJ_AIM, edi->font))
		return (-1);
	edi->script_obj_area.y = 70;
	if (!libui_create_label(&edi->label_script_obj_file, edi->script_obj_area,
		SCRIPT_EMPTY, edi->font))
		return (-1);
	libui_callback_sethover(&edi->area_script_obj, func_void2,
		SDL_MOUSEMOTION, NULL);
	libui_widgets_add_widget(ws, &edi->area_script_obj, 0,
		&edi->editor_container);
	libui_widgets_add_widget(ws, &edi->label_script_obj_aim, 0,
		&edi->area_script_obj);
	libui_widgets_add_widget(ws, &edi->label_script_obj_file, 0,
		&edi->area_script_obj);
	edi->script_obj_area = edi->area_script_obj.rect;
	return (add_delete_button(ws, edi, &edi->area_script_obj,
			&edi->button_disconnect_script_obj));
}
