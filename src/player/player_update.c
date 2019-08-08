/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:35:15 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/05 17:23:48 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void			player_update(t_e *e)
{
	e->main_player.entity.feet.onground = FALSE;
	e->main_player.entity.feet.look.a[0] = cos(e->input_map.mouse.pos.n.x * M_PI / 180.0);
	e->main_player.entity.feet.look.a[1] = 0;
	e->main_player.entity.feet.look.a[2] = sin(e->input_map.mouse.pos.n.x * M_PI / 180.0);
	update_entity(&e->world, &e->main_player.entity.feet);
	e->main_player.is_running = FALSE;
	update_player_sector(&e->main_player, &e->world);
}
