/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 23:28:35 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 17:56:54 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		render(t_e *e)
{
	t_vec3d		look_dir;

	look_dir = vec3vec3_add(e->camera.pos, e->input_map.mouse.front);
	mat4_init(&e->world.sectors[0].objects[3].mesh->matrix);
	mat4_scale(e->world.sectors[0].objects[3].mesh->matrix, 0.2, 0.2, 0.2);
	mat4_translate(e->world.sectors[0].objects[3].mesh->matrix, e->main_player.pos.a[0], e->main_player.pos.a[1], e->main_player.pos.a[2]);
	init_zbuff(e->win->surface->w * e->win->surface->h);
	mf_memset(get_zbuff(), 0, e->win->surface->w * e->win->surface->h * sizeof(double));
	libui_window_clear(e->win);
	e->camera.view_matrix = look_at(e->camera.pos, look_dir, (t_vec3d){.a = {0, -1, 0}});
	render_sector(get_sector(e->main_player.sector, &e->world), &e->camera, e->win->surface, NULL);
	draw_transparent(e->win->surface);
	libui_window_refresh(e->win);
}
