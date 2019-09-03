/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sector_gravity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:28:25 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/03 15:28:26 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_sector_gravity(t_editor_interface *edi)
{
	update_double_slider_data(&edi->slider_physics_gravity_x,
	&edi->label_nb_physics_gravity_x, edi->sector_gravity.n.x);
	update_double_slider_data(&edi->slider_physics_gravity_y,
	&edi->label_nb_physics_gravity_y, edi->sector_gravity.n.y);
	update_double_slider_data(&edi->slider_physics_gravity_z,
	&edi->label_nb_physics_gravity_z, edi->sector_gravity.n.z);
}
