/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:35:15 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/14 13:11:52 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void			player_update(t_e *e)
{
	e->main_player.on_ground = FALSE;
	e->main_player.direction[0] = cos(e->input_map.mouse.pos.x * M_PI / 180.0);
	e->main_player.direction[1] = 0;
	e->main_player.direction[2] = sin(e->input_map.mouse.pos.x * M_PI / 180.0);
	e->main_player.entity.look.x = e->main_player.direction[0];
	e->main_player.entity.look.y = e->main_player.direction[1];
	e->main_player.entity.look.z = e->main_player.direction[2];
	update_player_sector(&e->main_player, &e->world);
	e->main_player.entity.velocity.y = -1;
	if (update_entity(&e->world, &e->main_player.entity))
	{
		e->main_player.on_ground = TRUE;
		printf("collided!");
	}
	// vec3vec3_add(e->main_player.pos, e->main_player.velocity, e->main_player.pos);
	if (!e->main_player.on_ground)
		// e->main_player.velocity[1] -= (D_GRAVITY * DELTATIME);
		e->main_player.entity.velocity.y -= (D_GRAVITY * DELTATIME);
	/* fake floor, to be removed */
	// if (e->main_player.pos[1] < 0)
	// {
	// 	e->main_player.on_ground = TRUE;
	// 	e->main_player.velocity[1] = 0;
	// }
}
