/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_walk_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:29:02 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 16:28:17 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_walk_left(void *param)
{
	t_e		*e;
	double	vec2[3];
	double	vec3[3];

	e = param;
	if (e->main_player.on_ground)
	{
		vec3_copy(vec2, e->main_player.direction);
		vec3vec3_crossproduct(vec2, (double [3]){0, 1, 0}, vec3);
		vec3_normalize_s(vec3);
		vec3scalar_multiply(vec3, ACC_PLAYER_WALK, vec2);
		vec3vec3_add(e->main_player.velocity, vec2, e->main_player.velocity);
	}
}
