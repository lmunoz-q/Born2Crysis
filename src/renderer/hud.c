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

void	draw_rewind(unsigned int idc, t_texture *a, t_e *e)
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

void	draw_repeat(t_e *e)
{
    SDL_Rect	r;
    SDL_Surface *a;
    r.x = 0;
    r.y = 0;
    r.w = 160;
    r.h = 160;

    if (e->font == NULL)
        e->font = TTF_OpenFont("./libui/resources/Prototype.ttf", 16);
    a = TTF_RenderText_Solid(e->font, "Rewind", (SDL_Color){255, 255, 255, 255});
    SDL_BlitScaled(a, NULL, e->win->surface, &r);
    SDL_FreeSurface(a);
}

void	hud(t_e *e)
{
	unsigned int	id;
	unsigned int	idc;
	unsigned int    idr;
	t_texture		*jetpack;
	t_texture		*time;
	t_texture       *rewind;

	id = 0;
	idc = 0;
	idr = 0;
	rewind = NULL;
	time = NULL;
	jetpack = NULL;
	draw_jetpack(id, jetpack, e);
	if (e->main_player.entity.eidos.eidos_tick >= EIDOS_FRAMES)
		draw_rewind(idc, time, e);
	draw_repeat(e);
}
