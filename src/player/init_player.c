/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:58:24 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 17:02:19 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	init_player(t_player *p)
{
	p->sector = 0;
	p->on_ground = FALSE;
	p->is_running = FALSE;
	p->max_speed = DEFAULT_MAX_WALK_SPEED;
	p->acceleration[ACC_PLAYER_JUMP][0] = 0;
	p->acceleration[ACC_PLAYER_JUMP][1] = DEFAULT_JUMP_FORCE;
	p->acceleration[ACC_PLAYER_JUMP][2] = 0;
	vec3_clear(p->velocity);
	vec3_clear(p->pos);
	p->entity.velocity.x = p->velocity[0];
	p->entity.velocity.y = p->velocity[1];
	p->entity.velocity.z = p->velocity[2];
	p->entity.position = (t_double3){0, 0, 0};
	p->entity.sector = 0;
}
