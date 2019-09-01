/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:04:33 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/16 16:04:42 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <physic.h>
#include <world.h>

void	apply_effect(t_eidos_frame *e, t_world *w, t_effect effect)
{
	(void)w;
	if (effect == EFF_RESET_JUMP)
		e->can_jump = 1;
	if (effect == EFF_ACTIVATE_FLY)
	{
		e->can_go_down = 1;
		e->can_go_up = 1;
	}
	if (effect == EFF_DEACTIVATE_FLY)
	{
		e->can_go_down = 0;
		e->can_go_up = 0;
	}
}
