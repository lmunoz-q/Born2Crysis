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
	p->on_ground = FALSE;
	p->is_running = FALSE;
	p->max_speed = DEFAULT_MAX_WALK_SPEED;
	p->acceleration[ACC_PLAYER_JUMP].a[0] = 0;
	p->acceleration[ACC_PLAYER_JUMP].a[1] = DEFAULT_JUMP_FORCE;
	p->acceleration[ACC_PLAYER_JUMP].a[2] = 0;
	vec3_clear(&p->entity.feet.velocity);
	vec3_clear(&p->entity.feet.position);
	p->entity.feet.sector = 0;
	p->entity.top = 1.80;
}
