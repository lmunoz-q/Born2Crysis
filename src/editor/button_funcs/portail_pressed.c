/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portail_pressed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 15:50:25 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/20 18:51:08 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int	portail_pressed(SDL_Event *event, t_libui_widget *widget, void *data)
{
	t_editor_interface	*edi;

	(void)event;
	(void)widget;
	(void)data;
	edi = (t_editor_interface *)data;
	if (edi->is_making_portail == TRUE)
	{
		edi->is_making_portail = FALSE;
		libui_label_set_text(widget->shilds, "MESH");
	}
	else
	{
		edi->is_making_portail = TRUE;
		libui_label_set_text(widget->shilds, "PORTAIL");
	}
	return (0);
}
