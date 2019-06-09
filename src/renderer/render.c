/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 23:28:35 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/09 19:19:13 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		render(t_e *e)
{
	double		look_dir[3];

	vec3vec3_add(e->camera.pos, e->input_map.mouse.front, look_dir);
	init_zbuff(e->win->surface->w * e->win->surface->h);
	reset_zbuff(999999.9, e->win->surface->w * e->win->surface->h);
	libui_window_clear(e->win);
	look_at(e->camera.pos, look_dir, (double [3]){0, -1, 0}, e->camera.view_matrix);
	render_sector(get_sector(e->main_player.sector, &e->world), e->win, &e->camera);
	libui_window_refresh(e->win);
}
