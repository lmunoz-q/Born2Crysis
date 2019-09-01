/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_eidos_rewind.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 21:01:54 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/01 14:06:40 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <key_funcs.h>

void	kf_eidos_rewind(void *param)
{
	t_player_entity	*ent;

	ent = &((t_e*)param)->main_player.entity;
	if (ent->eidos.eidos_tick >= EIDOS_FRAMES)
		ent->eidos.active = TRUE;
	if (ent->eidos.active)
		ent->eidos.rewinding = 1;
}
