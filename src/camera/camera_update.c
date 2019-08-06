/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 20:25:02 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/13 20:48:35 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		camera_update(t_e *e)
{
	e->camera.pos = e->main_player.pos;
	e->camera.pos.n.y += CAMERA_HEIGHT;
}
