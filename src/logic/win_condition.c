/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_condition.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 14:07:25 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/27 14:10:53 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	win_condition(t_e *e)
{
	if (vec3vec3_dist(e->main_player.entity.body.position,
		e->world.goal_point) < WIN_RADIUS)
		e->game_running = FALSE;
}
