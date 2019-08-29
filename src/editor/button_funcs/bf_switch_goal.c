/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bf_switch_goal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 13:51:42 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/27 13:52:46 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		bf_switch_goal(SDL_Event *event, t_libui_widget *widget, void *data)
{
	t_editor_interface	*ei;

	(void)event;
	ei = data;
	if (ei->is_goal == TRUE)
	{
		ei->is_goal = FALSE;
		libui_label_set_text(widget->shilds, "GOAL");
	}
	else
	{
		ei->is_goal = TRUE;
		libui_label_set_text(widget->shilds, "[GOAL]");
	}
	return (0);
}
