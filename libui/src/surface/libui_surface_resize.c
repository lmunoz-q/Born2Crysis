/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_surface_resize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:31:36 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:31:36 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>

int	libui_surface_resize(SDL_Surface **surface, int width, int height)
{
	SDL_Surface	*tmp;
	SDL_Surface	*s;

	s = *surface;
	if ((tmp = SDL_CreateRGBSurface(s->flags, width, height,
			s->format->BitsPerPixel, s->format->Rmask, s->format->Gmask,
			s->format->Bmask, s->format->Amask)) == NULL)
		return (-1);
	if (SDL_BlitScaled(*surface, NULL, tmp, NULL) < 0)
	{
		SDL_FreeSurface(tmp);
		return (-1);
	}
	SDL_FreeSurface(*surface);
	*surface = tmp;
	return (0);
}
