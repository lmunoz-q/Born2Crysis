/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:58:24 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/13 20:47:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	init_player(t_player *p)
{
	p->sector = 0;
	p->on_ground = FALSE;
	vec3_clear(p->velocity);
	vec3_clear(p->pos);
}
