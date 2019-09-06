/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_wall_friction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:32:24 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/05 18:04:11 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	update_wall_friction(t_editor_interface *edi)
{
	update_double_slider_data(&edi->slider_physics_wall_friction,
	&edi->label_nb_physics_wall_friction, edi->wall_friction);
}
