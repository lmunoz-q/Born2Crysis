/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_pixel_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:26:59 by hmartzol          #+#    #+#             */
/*   Updated: 2019/03/05 20:27:01 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_pixel.h>

Uint32	libui_pixel_get(SDL_Surface *surface, int x, int y)
{
	int		bpp;
	Uint8	*p;

	if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
		return (0);
	bpp = surface->format->BytesPerPixel;
	p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	if (bpp == 2)
		return (*(Uint16*)p);
	if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (((Uint32)p[0] << 16) | ((Uint32)p[1] << 8) | (Uint32)p[2]);
		else
			return (((Uint32)p[2] << 16) | ((Uint32)p[1] << 8) | (Uint32)p[0]);
	}
	if (bpp == 4)
		return (*(Uint32*)p);
	return (0);
}

Uint32	libui_pixel_get_atomic(SDL_Surface *surface, int x, int y)
{
	int		bpp;
	Uint8	*p;
	Uint32	out;

	out = 0;
	SDL_LockSurface(surface);
	if (x >= 0 && x < surface->w && y >= 0 && y < surface->h)
	{
		bpp = surface->format->BytesPerPixel;
		p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
		if (bpp == 1)
			out = *p;
		if (bpp == 2)
			out = *(Uint16*)p;
		if (bpp == 3)
			out = (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				? (((Uint32)p[0] << 16) | ((Uint32)p[1] << 8) | (Uint32)p[2])
				: (((Uint32)p[2] << 16) | ((Uint32)p[1] << 8) | (Uint32)p[0]);
		if (bpp == 4)
			out = *(Uint32*)p;
	}
	SDL_UnlockSurface(surface);
	return (out);
}
