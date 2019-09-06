/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sector_friction.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:34:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/03 15:34:26 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_sector_friction(t_editor_interface *edi)
{
	update_double_slider_data(&edi->slider_physics_gbl_fric_x,
	&edi->label_nb_physics_gbl_fric_x, edi->sector_global_friction.n.x);
	update_double_slider_data(&edi->slider_physics_gbl_fric_y,
	&edi->label_nb_physics_gbl_fric_y, edi->sector_global_friction.n.y);
	update_double_slider_data(&edi->slider_physics_gbl_fric_z,
	&edi->label_nb_physics_gbl_fric_z, edi->sector_global_friction.n.z);
}
