/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_pixel_draw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:30:15 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:30:16 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_pixel.h>

/*
** expect a 32bit surface created by this library, will use the alpha part of
** the color to do a blendig with the current surface color
*/

int	libui_pixel_draw(SDL_Surface *surface, int x, int y, Uint32 color)
{
	t_libui_pixel_color	c1;
	t_libui_pixel_color	c2;
	Uint32				*ptr;
	double				m;

	c1.u32 = color;
	if (c1.c.a == 0)
		return (0);
	ptr = &((Uint32*)surface->pixels)[x + y * surface->w];
	if (c1.c.a != 255)
	{
		m = 255. / (double)c1.c.a;
		c2.u32 = *ptr;
		c1.c.a = 255;
		c1.c.r = (Uint8)(c1.c.r * m + c2.c.r * (1. - m));
		c1.c.g = (Uint8)(c1.c.g * m + c2.c.g * (1. - m));
		c1.c.b = (Uint8)(c1.c.b * m + c2.c.b * (1. - m));
	}
	*ptr = c1.u32;
	return (0);
}

int	libui_pixel_draw_atomic(SDL_Surface *surface, int x, int y, Uint32 color)
{
	t_libui_pixel_color	c1;
	t_libui_pixel_color	c2;
	Uint32				*ptr;
	double				m;

	c1.u32 = color;
	if (c1.c.a == 0)
		return (0);
	SDL_LockSurface(surface);
	ptr = &((Uint32*)surface->pixels)[x + y * surface->w];
	if (c1.c.a != 255)
	{
		m = 255. / (double)c1.c.a;
		c2.u32 = *ptr;
		c1.c.a = 255;
		c1.c.r = (Uint8)(c1.c.r * m + c2.c.r * (1. - m));
		c1.c.g = (Uint8)(c1.c.g * m + c2.c.g * (1. - m));
		c1.c.b = (Uint8)(c1.c.b * m + c2.c.b * (1. - m));
	}
	*ptr = c1.u32;
	SDL_UnlockSurface(surface);
	return (0);
}
