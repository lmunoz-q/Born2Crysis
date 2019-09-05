/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_pixel_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:27:03 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/22 16:30:51 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_pixel.h>

/*
** transform a x/y = [-1, 1] coordinate to a x/y = [0, w/h] coordinate
** note: the x and y values aren't clamped to [-1, 1]
*/

t_libui_pixel_coord	libui_pixel_coord_centered(SDL_Surface *surface,
	double x, double y)
{
	return ((t_libui_pixel_coord){.x = (int)(((x + 1) / 2) * surface->w),
								.y = (int)(((y + 1) / 2) * surface->h)});
}

int					libui_pixel_set(SDL_Surface *surface, int x, int y,
	Uint32 color)
{
	int		bpp;
	Uint8	*ptr;

	if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
		return (-1);
	bpp = surface->format->BytesPerPixel;
	ptr = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		*ptr = (Uint8)color;
	if (bpp == 2)
		*(Uint16*)ptr = (Uint16)color;
	if (bpp == 3)
	{
		ptr[2 - 2 * (SDL_BYTEORDER == SDL_BIG_ENDIAN)] = (Uint8)(color >> 16);
		ptr[1] = (Uint8)(color >> 8);
		ptr[2 * (SDL_BYTEORDER == SDL_BIG_ENDIAN)] = (Uint8)color;
	}
	if (bpp == 4)
		*(Uint32*)ptr = color;
	return (0);
}

int					libui_pixel_set_atomic(SDL_Surface *surface, int x, int y,
	Uint32 color)
{
	int		bpp;
	Uint8	*ptr;

	SDL_LockSurface(surface);
	if (x < 0 || x >= surface->w || y < 0 || y >= surface->h)
	{
		SDL_UnlockSurface(surface);
		return (-1);
	}
	bpp = surface->format->BytesPerPixel;
	ptr = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		*ptr = (Uint8)color;
	if (bpp == 2)
		*(Uint16*)ptr = (Uint16)color;
	if (bpp == 3)
	{
		ptr[2 - 2 * (SDL_BYTEORDER == SDL_BIG_ENDIAN)] = (Uint8)(color >> 16);
		ptr[1] = (Uint8)(color >> 8);
		ptr[2 * (SDL_BYTEORDER == SDL_BIG_ENDIAN)] = (Uint8)color;
	}
	if (bpp == 4)
		*(Uint32*)ptr = color;
	SDL_UnlockSurface(surface);
	return (0);
}
