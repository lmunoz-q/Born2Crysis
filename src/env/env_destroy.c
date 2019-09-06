/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 10:51:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/01 18:44:57 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		env_destroy(t_e *e)
{
	libui_window_delete(e->win);
	gthread_destroy(gthread_get(GTHREAD_PREVIEW));
	gthread_destroy(gthread_get(GTHREAD_EDITOR));
	gthread_destroy(gthread_get(GTHREAD_GAME));
	world_destroy(&e->world);
	destroy_zbuff();
	sector_queue_push((t_sector *)-1);
	buffer_destroy();
	transbuff_destroy();
}
