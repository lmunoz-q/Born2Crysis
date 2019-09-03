/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sector_drag.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:29:03 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/03 15:29:04 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_sector_drag(t_editor_interface *edi)
{
	update_double_slider_data(&edi->slider_physics_drag_x,
	&edi->label_nb_physics_drag_x, edi->sector_drag.n.x);
	update_double_slider_data(&edi->slider_physics_drag_y,
	&edi->label_nb_physics_drag_y, edi->sector_drag.n.y);
	update_double_slider_data(&edi->slider_physics_drag_z,
	&edi->label_nb_physics_drag_z, edi->sector_drag.n.z);
}
