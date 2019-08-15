/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:58:24 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/05 16:39:44 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	init_player(t_player *p)
{
	p->is_running = FALSE;
	p->max_speed = DEFAULT_MAX_WALK_SPEED;
	p->acceleration[ACC_PLAYER_JUMP].a[0] = 0;
	p->acceleration[ACC_PLAYER_JUMP].a[1] = DEFAULT_JUMP_FORCE;
	p->acceleration[ACC_PLAYER_JUMP].a[2] = 0;
	vec3_clear(&p->entity.body.velocity);
	vec3_clear(&p->entity.body.position);
	p->entity.body = (t_entity){
		.flags = EF_FRICTION | EF_GRAVITY | EF_CLIP,
		.position = {{0, 0, 0}},
		.radius = 0.5,
		.height = 1.8,
		.sector = 0,
		.look = {{1, 0, 0}}};
	p->entity.body.can_jump = 0;
	p->entity.body.can_go_up = 1;
	p->entity.body.can_go_down = 1;
}
