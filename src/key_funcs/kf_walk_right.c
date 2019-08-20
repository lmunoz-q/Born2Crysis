/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_walk_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:31:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/21 01:00:49 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_walk_right(void *param)
{
	t_e				*e;
	union u_vec3d	a;
	union u_vec3d	b;

	e = param;
	(void)a;
	a = e->main_player.entity.body.velocity;
	b = e->main_player.entity.body.look;
	e->main_player.entity.body.velocity = entity_accelerate(e->main_player.entity.body, vec3scalar_multiply(vec3_normalize(vec3vec3_crossproduct(b, (t_vec3d){{0, 1, 0}})), -ACC_PLAYER_WALK));
}

/*
** if (e->main_player.on_ground)
*/
