/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_endscreen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:24:59 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 20:18:27 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	update_endscreen_mesh(t_mesh *mesh, double *p)
{
	int i;
	int j;
	int	t;

	t = -1;
	i = -1;
	while (++i < 100 - 1)
	{
		j = -1;
		while (++j < 100 - 1)
		{
			mesh->polygons[++t].v01.n.y = 20 * p[(i * 100) + (j % 100)];
			mesh->polygons[t].v12.n.y = 20 * p[(i * 100) + ((j + 1) % 100)];
			mesh->polygons[t].v20.n.y = 20 * p[((i + 1) * 100) + ((j + 1) % 100)];
			mesh->polygons[++t].v01.n.y = 20 * p[(i * 100) + (j % 100)];
			mesh->polygons[t].v12.n.y = 20 * p[((i + 1) * 100) + ((j + 1) % 100)];
			mesh->polygons[t].v20.n.y = 20 * p[((i + 1) * 100) + ((j) % 100)];
		}
	}
}

static void	render_perlin_mesh(t_e *e)
{
	static double	*perlin = NULL;
	t_vec3d			look_dir;

	if (e == NULL)
	{
		if (perlin)
			free(perlin);
		return ;
	}
	look_dir = vec3vec3_add(e->camera.pos, e->input_map.mouse.front);
	e->camera.view_matrix = look_at(e->camera.pos, look_dir, (t_vec3d){.a
	= {0, -1, 0}});
	if (!perlin)
	{
		perlin = gen_perlin((t_vec2i){.a = {100, 100}}, SDL_GetTicks(), 7, 1.8);
		if (perlin)
		{
			update_endscreen_mesh(e->endscreen, perlin);
			free(perlin);
		}
	}
	render_wireframe_mesh(e->endscreen, &e->camera, e->win->surface, 0xffff0000);
}

void	render_endscreen(t_e *e)
{
	SDL_Rect	r;
	
	if (!e)
	{
		render_perlin_mesh(NULL);
		return ;
	}
	r = (SDL_Rect){.x = e->win->surface->w / 4, .y = e->win->surface->h / 4,
			.h = e->win->surface->h / 2, .w = e->win->surface->w / 2};
	mat4_init(&e->camera.view_matrix);
	vec3_clear(&e->camera.pos);
	libui_window_clear(e->win);
	render_perlin_mesh(e);
	if (e->stats.win)
		SDL_BlitScaled(get_texture_from_id(
			load_texture_from_x("assets/endscreens/win.png", TX_CLAMP_EDGES))->texture,
				NULL, e->win->surface, &r);
	else
		SDL_BlitScaled(get_texture_from_id(
			load_texture_from_x("assets/endscreens/gameover.jpg", TX_CLAMP_EDGES))->texture,
				NULL, e->win->surface, &r);
	libui_window_refresh(e->win);
}