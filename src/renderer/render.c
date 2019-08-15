/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 23:28:35 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/25 00:03:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		render(t_e *e)
{
	t_vec3d		look_dir;

	look_dir = vec3vec3_add(e->camera.pos, e->input_map.mouse.front);
	mf_memset(get_zbuff(), 0, e->win->surface->w * e->win->surface->h
	* sizeof(double));
	libui_window_clear(e->win);
	e->camera.view_matrix = look_at(e->camera.pos, look_dir, (t_vec3d){.a
	= {0, -1, 0}});
	render_sector(get_sector(e->main_player.entity.body.sector, &e->world),
		&e->camera, e->win->surface, NULL);
	skybox_set_pos(e->world.skybox, e->main_player.entity.body.position);
	render_mesh(e->world.skybox->mesh, &e->camera, e->win->surface, NULL);
	draw_transparent(e->win->surface);
	libui_window_refresh(e->win);
}
