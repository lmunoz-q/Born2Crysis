/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_crouch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 13:03:10 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/05 16:37:16 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_crouch(void *param)
{
	t_e		*e;

	e = param;
	if (e->main_player.entity.body.can_go_down)
	{
		if (e->main_player.entity.body.velocity.n.y > -1)
			e->main_player.entity.body.velocity.n.y -= 0.2;
	}
	else
	{
		if (e->main_player.entity.pse == PSE_CROUCH)
			e->main_player.entity.pse = PSE_NORMAL;
		else
			e->main_player.entity.pse = PSE_CROUCH;
	}
}
