/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:17:02 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/28 15:43:16 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		update(t_e *e)
{
	player_update(e);
	camera_update(e);
	win_condition(e);
	if (e->world.sectors->lights.lights)
	{
		mat4_init(&e->world.sectors->lights.lights->mat);
		e->world.sectors->lights.lights->mat = mat4_translate(e->world.sectors->
			lights.lights->mat, e->main_player.entity.body.position.n.x,
			e->main_player.entity.body.position.n.y,
			e->main_player.entity.body.position.n.z);
	}
}
