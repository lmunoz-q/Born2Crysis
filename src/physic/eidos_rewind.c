/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eidos_rewind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 14:09:19 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/01 14:09:21 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

int	eidos_rewind(t_player_entity *player)
{
	t_vec3d	look;

	if (player->eidos.eidos_tick > SAFE_FRAMES - 1)
	{
		look = player->body.look;
		--player->eidos.eidos_tick;
		player->body = player->eidos.eidos_save[--player->eidos.eidos_tick];
		player->body.look = look;
		player->body.velocity = (t_vec3d){{0, 0, 0}};
	}
	else
		player->eidos.active = FALSE;
	player->eidos.rewinding = 0;
	return (0);
}