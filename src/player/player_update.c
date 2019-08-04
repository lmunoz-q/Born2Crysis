/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:35:15 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 17:04:19 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		player_apply_basic_physics(t_e *e)
{
	double	ratio;

	e->main_player.max_speed = (e->main_player.is_running) ? DEFAULT_MAX_RUN_SPEED : DEFAULT_MAX_WALK_SPEED;
	e->main_player.entity.feet.position = vec3vec3_add(e->main_player.entity.feet.position, e->main_player.entity.feet.velocity);
	if (e->main_player.entity.feet.position.a[1] < 0)
	{
		e->main_player.on_ground = TRUE;
		e->main_player.entity.feet.velocity.a[1] = 0;
	}
	if (!e->main_player.on_ground)
		e->main_player.entity.feet.velocity.a[1] -= (D_GRAVITY * DELTATIME);
	else
	{
		e->main_player.entity.feet.velocity.a[0] *= DEFAULT_FRICTION;
		e->main_player.entity.feet.velocity.a[2] *= DEFAULT_FRICTION;
	}
	if (vec3_magnitude(e->main_player.entity.feet.velocity) > e->main_player.max_speed && e->main_player.on_ground)
	{
		ratio = e->main_player.max_speed / vec3_magnitude(e->main_player.entity.feet.velocity);
		e->main_player.entity.feet.velocity.a[0] *= ratio;
		e->main_player.entity.feet.velocity.a[2] *= ratio;
	}
}

void			player_update(t_e *e)
{
	e->main_player.on_ground = FALSE;
	e->main_player.entity.feet.look.a[0] = cos(e->input_map.mouse.pos.n.x * M_PI / 180.0);
	e->main_player.entity.feet.look.a[1] = 0;
	e->main_player.entity.feet.look.a[2] = sin(e->input_map.mouse.pos.n.x * M_PI / 180.0);
//	update_player_sector(&e->main_player, &e->world);
//	player_apply_basic_physics(e);
	if (update_entity(&e->world, &e->main_player.entity.feet))
	// {
		// e->main_player.entity.feet.velocity.n.y = 0;
//		printf("**** COLLISION *****\n");
// 	}
	e->main_player.is_running = FALSE;
}
