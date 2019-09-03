/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_is_physics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:19:09 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/03 15:20:20 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_is_physics(t_editor_interface *edi)
{
	if (edi->is_physics == TRUE)
	{
		libui_label_set_text(edi->physics_textbutton.shilds, "PHYSICS (OFF)");
	}
	else
	{
		libui_label_set_text(edi->physics_textbutton.shilds, "PHYSICS (ON)");
	}
}
