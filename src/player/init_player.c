/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:58:24 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 17:21:47 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	init_entity_body(t_player *p, t_world *world)
{
	p->entity.body = (t_eidos_frame){
		.flags = EF_FRICTION | EF_GRAVITY | EF_CLIP | EF_ACTIVATE,
		.position = {{0, 0, 0}},
		.radius = 2.5,
		.height = 8,
		.sector = &world->sectors[0],
		.look = {{1, 0, 0}},
		.can_jump = 0,
		.can_go_up = 0,
		.can_go_down = 0};
}

void	init_player(t_player *p, t_world *world)
{
	p->is_running = FALSE;
	p->max_speed = DEFAULT_MAX_WALK_SPEED;
	p->acceleration[ACC_PLAYER_JUMP].a[0] = 0;
	p->acceleration[ACC_PLAYER_JUMP].a[1] = DEFAULT_JUMP_FORCE;
	p->acceleration[ACC_PLAYER_JUMP].a[2] = 0;
	vec3_clear(&p->entity.body.velocity);
	vec3_clear(&p->entity.body.position);
	init_entity_body(p, world);
	p->entity.wall_detection = (t_eidos_frame){
		.flags = EF_ACTIVATE,
		.position = {{0, 0.5, 0}},
		.radius = 2.5,
		.height = 1,
		.sector = &world->sectors[0],
		.look = {{1, 0, 0}},
		.can_jump = 0,
		.can_go_up = 0,
		.can_go_down = 0};
}
