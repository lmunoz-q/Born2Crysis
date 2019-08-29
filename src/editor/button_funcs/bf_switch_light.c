/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bf_switch_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 13:29:59 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 13:37:00 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		bf_switch_light(SDL_Event *event, t_libui_widget *widget, void *data)
{
	t_editor_interface	*ei;

	(void)event;
	ei = data;
	if (ei->is_light == TRUE)
	{
		ei->is_light = FALSE;
		libui_label_set_text(widget->shilds, "LIGHT (OFF)");
	}
	else
	{
		ei->is_light = TRUE;
		libui_label_set_text(widget->shilds, "LIGHT (ON)");
	}
	return (0);
}
