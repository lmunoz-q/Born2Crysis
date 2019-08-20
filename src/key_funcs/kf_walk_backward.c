/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_walk_backward.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:40:09 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 16:28:30 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_walk_backward(void *param)
{
	t_e		*e;

	e = param;
	e->main_player.entity.body.velocity = entity_accelerate(e->main_player.entity.body, vec3scalar_multiply(e->main_player.entity.body.look, ACC_PLAYER_WALK));
}

/*
**	if (e->main_player.on_ground)
*/
