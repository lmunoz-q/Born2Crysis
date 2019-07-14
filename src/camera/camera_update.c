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

void		camera_update(t_e	*e)
{
	vec3_copy(e->camera.pos, e->main_player.pos);
	e->camera.pos[1] += CAMERA_HEIGHT;
}
