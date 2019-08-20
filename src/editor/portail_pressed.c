/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portail_pressed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:50:25 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/20 17:41:06 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int portail_pressed(SDL_Event *event, t_libui_widget *widget, void *data)
{
	(void)event;
	(void)widget;
	(void)data;
	t_editor_interface *edi;

	edi = (t_editor_interface *)data;
	if (edi->is_making_portail == SDL_TRUE)
	{
		edi->is_making_portail = SDL_FALSE;
		libui_label_set_text(widget->shilds, "MESH");
	}
	else
	{
		edi->is_making_portail = SDL_TRUE;
		libui_label_set_text(widget->shilds, "PORTAIL");
	}
	return (0);
}
