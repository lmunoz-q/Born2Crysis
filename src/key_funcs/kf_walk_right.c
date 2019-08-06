/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_walk_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:31:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 16:28:24 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_walk_right(void *param)
{
	t_e		*e;

	e = param;
	if (e->main_player.on_ground)
	{
		e->main_player.velocity = vec3vec3_substract(e->main_player.velocity, vec3scalar_multiply(vec3_normalize(vec3vec3_crossproduct(e->main_player.direction, (t_vec3d){.a = {0, 1, 0}})), ACC_PLAYER_WALK));
	}
}
