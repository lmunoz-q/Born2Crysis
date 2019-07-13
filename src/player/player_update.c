/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:35:15 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/13 20:49:33 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void			player_update(t_e *e)
{
	update_player_sector(&e->main_player, &e->world);
	vec3vec3_add(e->main_player.pos, e->main_player.velocity, e->main_player.pos);
}