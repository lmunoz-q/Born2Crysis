/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:02:58 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/09/03 17:03:00 by lmunoz-q         ###   ########.fr       */
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

void	draw_crouch(unsigned int idc, t_texture *a, t_e *e)
{
	SDL_Rect	r;

	r.x = 80;
	r.y = 10;
	r.w = 80;
	r.h = 60;

	idc = load_texture_from_x("assets/HUD/time.bmp", TX_CLAMP_EDGES);
	a = get_texture_from_id(idc);
	SDL_BlitScaled(a->texture, NULL, e->win->surface, &r);
}

void	hud(t_e *e)
{
	unsigned int	id;
	unsigned int	idc;
	t_texture		*jetpack;
	t_texture		*time;

	id = 0;
	idc = 0;
	time = NULL;
	jetpack = NULL;
	draw_jetpack(id, jetpack, e);
	draw_crouch(idc, time, e);
}
