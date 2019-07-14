/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_walk_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:29:02 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/13 21:56:12 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_walk_left(void *param)
{
	t_e		*e;
	double	vec[3];
	double	vec2[3];
	double	vec3[3];

	e = param;
	vec3_copy(vec, e->main_player.pos);
	vec3_copy(vec2, e->main_player.direction);
	vec3vec3_crossproduct(vec2, (double [3]){0, 1, 0}, vec3);
	vec3_normalize_s(vec3);
	vec3scalar_multiply(vec3, 0.2, vec2);
	vec3vec3_add(vec, vec2, e->main_player.pos);
}
