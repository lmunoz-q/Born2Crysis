/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_is_goal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:20:41 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/03 15:20:42 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_is_goal(t_editor_interface *edi)
{
	if (edi->is_goal == TRUE)
	{
		libui_label_set_text(edi->physics_textbutton.shilds, "GOAL");
	}
	else
	{
		libui_label_set_text(edi->physics_textbutton.shilds, "[GOAL]");
	}
}
