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

void	hud(t_e *e)
{
	unsigned int	id;
	t_texture		*a;
	SDL_Rect		r;

	r.x = 0;
	r.y = 0;
	r.w = 500;
	r.y = 500;
	id = load_texture_from_x("assets/HUD/jet-pack.bmp", TX_CLAMP_EDGES);
	a = get_texture_from_id(id);
	printf("%d\n", SDL_BlitScaled(a->texture, NULL, e->win->surface, &r));
}

/*
#include "doom_nukem.h"

void	hud(t_e *e)
{
	unsigned int	id;
	t_texture		*a;
	SDL_Rect		r;

	r.x = 0;
	r.y = 0;
	r.w = 500;
	r.h = 500;
	id = load_texture_from_x("assets/HUD/jet-pack.bmp", TX_CLAMP_EDGES);
	a = get_texture_from_id(id);
	SDL_BlitScaled(a->texture, NULL, e->win->surface, &r);
}
*/
