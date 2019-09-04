/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:02:58 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/09/04 20:39:08 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_jetpack(unsigned int id, t_texture *a, t_e *e)
{
	SDL_Rect	r;

	r.x = 10;
	r.y = 10;
	r.w = 60;
	r.h = 60;
	id = load_texture_from_x("assets/HUD/jet-pack.bmp", TX_CLAMP_EDGES);
	a = get_texture_from_id(id);
	SDL_BlitScaled(a->texture, NULL, e->win->surface, &r);
}

void    draw_rewind(unsigned int idc, t_texture *a, t_e *e)
{
	SDL_Rect    r;

	r.x = 80;
	r.y = 10;
	r.w = 80;
	r.h = 60;

	idc = load_texture_from_x("assets/HUD/time.bmp", TX_CLAMP_EDGES);
	a = get_texture_from_id(idc);
	SDL_BlitScaled(a->texture, NULL, e->win->surface, &r);
}

<<<<<<< HEAD
void    hud(t_e *e)
=======
void	hud(t_e *e)
>>>>>>> f274a4b940aca95d07ba73d768e6f2edd5805e50
{
	unsigned int	id;
	t_texture		*tex;

	id = 0;
	tex = NULL;
	draw_jetpack(id, tex, e);
	if (e->main_player.entity.eidos.eidos_tick >= EIDOS_FRAMES)
		draw_rewind(id, tex, e);
}
