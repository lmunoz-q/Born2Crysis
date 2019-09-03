/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_wall_friction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:32:24 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/03 15:34:20 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_wall_friction(t_editor_interface *edi)
{
	//char	new_text[BASE_TEXT_SIZE + 1];

	update_double_slider_data(&edi->slider_physics_wall_friction,
	&edi->label_nb_physics_wall_friction, edi->wall_friction);
	/* doom_clean_text(new_text, BASE_TEXT_SIZE);
	if (edi->wall_friction_is_auto)
		doom_fill_text(new_text, WALL_FRICTION_AUTO_TEXT, FRICTION_TYPE_TEXT);
	else
		doom_fill_text(new_text, WALL_FRICTION_MAN_TEXT, FRICTION_TYPE_TEXT);
	libui_label_set_text(&edi->label_nb_physics_wall_friction, new_text);*/
}