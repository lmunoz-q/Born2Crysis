/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sector_physics.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 14:59:55 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/05 15:20:09 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

void	update_sector_physics(t_e *e)
{
	t_sector	*sector;

	sector = get_sector(e->editor.secteur_courant, &e->world);
	if (!sector)
		return ;
	sector->physics.drag = e->editor.sector_drag;
	sector->physics.global_friction = e->editor.sector_global_friction;
	sector->physics.speed_limit = e->editor.sector_speed_limit;
	sector->physics.gravity = e->editor.sector_gravity;
}
