/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_walk_backward.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:40:09 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 16:28:30 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_walk_backward(void *param)
{
	t_e		*e;
	double	vec2[3];

	e = param;
	if (e->main_player.on_ground)
	{
		vec3scalar_multiply(e->main_player.direction, ACC_PLAYER_WALK, vec2);
		vec3vec3_add(e->main_player.velocity, vec2, e->main_player.velocity);
	}
}
