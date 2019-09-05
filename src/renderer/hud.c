/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:02:58 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/09/05 18:49:50 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_jetpack(t_e *e)
{
	SDL_Rect	r;
	SDL_Rect	b;

	r.x = 10;
	r.y = 10;
	r.w = 60;
	r.h = 60;
	b = (SDL_Rect){.x = 115, .y = 25, .w = 68, .h = 55};
	if (e->main_player.entity.pse != PSE_CROUCH)
		SDL_BlitScaled(get_texture_from_id(
			load_texture_from_x("assets/HUD/crouch.jpg",
				TX_CLAMP_EDGES))->texture, &b, e->win->surface, &r);
	else
	{
		b = (SDL_Rect){.x = 115, .y = 122, .w = 68, .h = 55};
		SDL_BlitScaled(get_texture_from_id(
			load_texture_from_x("assets/HUD/crouch.jpg",
			TX_CLAMP_EDGES))->texture, &b, e->win->surface, &r);
	}
}

void	draw_rewind(unsigned int idc, t_texture *a, t_e *e)
{
	SDL_Rect    r;

	r.x = 80;
	r.y = 10;
	r.w = 80;
	r.h = 60;
	if (e->main_player.entity.eidos.eidos_tick >= EIDOS_MINIMUM_FRAMES)
	{
		idc = load_texture_from_x("assets/HUD/time.bmp", TX_CLAMP_EDGES);
		a   = get_texture_from_id(idc);
		SDL_BlitScaled(a->texture, NULL, e->win->surface, &r);
	}
}

void	draw_dist(t_e *e)
{
	SDL_Surface				*tmp;
	SDL_Color				color;
	TTF_Font				*font;

	color = (SDL_Color){255, 255, 255, 255};
	font = TTF_OpenFont("./libui/resources/Prototype.ttf", 16);
	if (font)
	{
		if ((tmp = TTF_RenderText_Solid(font, mf_sprintf("Goal is %.0fm away",
		vec3vec3_dist(e->main_player.entity.body.position,
		e->world.goal_point)), color)))
		{
			SDL_BlitSurface(tmp, NULL,
			e->win->surface, &(SDL_Rect){0, 400, 500, 500});
			SDL_FreeSurface(tmp);
		}
		TTF_CloseFont(font);
	}
}

void	hud(t_e *e)
{
	unsigned int	id;
	t_texture		*tex;

	id = 0;
	tex = NULL;
	draw_jetpack(e);
	draw_dist(e);
	draw_rewind(id, tex, e);
}
