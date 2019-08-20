/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_jump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 13:03:10 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/05 16:37:16 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_jump(void *param)
{
	t_e		*e;

	e = param;
	if (e->main_player.entity.body.can_jump)
	{
		e->main_player.entity.body.velocity =
			vec3vec3_add(e->main_player.entity.body.velocity,
				e->main_player.acceleration[ACC_PLAYER_JUMP]);
		e->main_player.entity.body.can_jump = 0;
	}
	else if (e->main_player.entity.body.can_go_up)
	{
		if (e->main_player.entity.body.velocity.n.y < 1)
			e->main_player.entity.body.velocity.n.y += 0.2;
	}
}
