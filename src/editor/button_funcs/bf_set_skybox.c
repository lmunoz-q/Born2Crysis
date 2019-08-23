/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bf_set_skybox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 09:52:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/23 09:57:17 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		bf_set_skybox(SDL_Event *event, t_libui_widget *widget,
							void *data)
{
	t_e *e;

	(void)event;
	(void)widget;
	e = data;
	if (e->world.skybox)
		mesh_delete(&e->world.skybox, 1, 0);
	e->world.skybox = mesh_copy(e->editor.item_placer);
	return (0);
}