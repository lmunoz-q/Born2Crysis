/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:35:15 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 16:53:25 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void		player_apply_basic_physics(t_e *e)
{
	double	ratio;
	
	vec3vec3_add(e->main_player.pos, e->main_player.velocity, e->main_player.pos);
	if (e->main_player.pos[1] < 0)
	{
		e->main_player.on_ground = TRUE;
		e->main_player.velocity[1] = 0;
	}
	if (!e->main_player.on_ground)
		e->main_player.velocity[1] -= (D_GRAVITY * DELTATIME);
	else
	{
		e->main_player.velocity[0] *= DEFAULT_FRICTION;
		e->main_player.velocity[2] *= DEFAULT_FRICTION;
	}
	if (vec3_magnitude(e->main_player.velocity) > DEFAULT_MAX_SPEED && e->main_player.on_ground)
	{
		ratio = DEFAULT_MAX_SPEED / vec3_magnitude(e->main_player.velocity);
		e->main_player.velocity[0] *= ratio;
		e->main_player.velocity[2] *= ratio;
	}
}

void			player_update(t_e *e)
{
	e->main_player.on_ground = FALSE;
	e->main_player.direction[0] = cos(e->input_map.mouse.pos.x * M_PI / 180.0);
	e->main_player.direction[1] = 0;
	e->main_player.direction[2] = sin(e->input_map.mouse.pos.x * M_PI / 180.0);
	update_player_sector(&e->main_player, &e->world);
	player_apply_basic_physics(e);
	/* fake floor, to be removed */
}
