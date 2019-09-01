/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eidos_rewind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2000/00/00 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

int	eidos_rewind(t_player_entity *player)
{
	t_vec3d	look;

	if (player->eidos.eidos_tick > SAFE_FRAMES)
	{
		look = player->body.look;
		player->body = player->eidos.eidos_save[--player->eidos.eidos_tick];
		player->body.look = look;
		player->body.velocity = (t_vec3d){{0, 0, 0}};
	}
	player->eidos.rewinding = 0;
	return (0);
}
