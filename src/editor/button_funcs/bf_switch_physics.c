/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bf_switch_physics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 21:50:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/23 21:55:04 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		bf_switch_physics(SDL_Event *event, t_libui_widget *widget,
							void *data)
{
	t_editor_interface	*ei;
	(void)event;

	ei = data;
	if (ei->is_physics == TRUE)
	{
		ei->is_physics = FALSE;
		libui_label_set_text(widget->shilds, "PHYSICS (OFF)");
	}
	else
	{
		ei->is_physics = TRUE;
		libui_label_set_text(widget->shilds, "PHYSICS (ON)");
	}
	return (0);
}