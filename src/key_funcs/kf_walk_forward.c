/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_walk_forward.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:34:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/28 16:34:45 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_walk_forward(void *param)
{
	t_e		*e;

	e = param;
	e->main_player.entity.body.velocity = entity_accelerate(e->main_player.
		entity.body, vec3scalar_multiply(e->main_player.entity.body.look,
			-ACC_PLAYER_WALK));
}
