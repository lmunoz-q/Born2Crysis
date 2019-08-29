/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:35:15 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/25 15:51:01 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			player_update(t_e *e)
{
	e->main_player.entity.body.look.a[0] = cos(e->input_map.mouse.pos.n.x
		* M_PI / 180.0);
	e->main_player.entity.body.look.a[1] = 0;
	e->main_player.entity.body.look.a[2] = sin(e->input_map.mouse.pos.n.x
		* M_PI / 180.0);
	e->main_player.entity.wall_detection = e->main_player.entity.body;
	e->main_player.entity.wall_detection.flags = EF_ACTIVATE;
	e->main_player.entity.wall_detection.position.n.y += 0.5;
	e->main_player.entity.wall_detection.radius = 2.5;
	e->main_player.entity.wall_detection.height = 1;
	e->main_player.entity.wall_detection.can_jump = 0;
	e->main_player.entity.wall_detection.can_go_up = 0;
	e->main_player.entity.wall_detection.can_go_down = 0;
	if (update_entity(&e->world, &e->main_player.entity.body)
	&& vec3_magnitude(e->main_player.entity.body.velocity) > 0.2)
		if (Mix_Playing(2) == 0)
			Mix_PlayChannel(2, e->sound.step, 0);
	update_entity_sector(&e->main_player.entity.body, &e->world);
}
