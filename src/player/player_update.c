/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:35:15 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/27 22:56:35 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void			player_update(t_e *e)
{
	vec3_copy(e->main_player.pos, e->camera.pos);
	update_player_sector(&e->main_player, &e->world);
}