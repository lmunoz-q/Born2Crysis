/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_pixel_draw_horizontal_line.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:26:45 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/22 16:29:46 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_pixel.h>

int	libui_pixel_draw_horizontal_line(SDL_Surface *surface,
	t_libui_pixel_coord point, int length, Uint32 color)
{
	int	i;

	if (length > 0)
	{
		i = -1;
		while (++i < length)
			libui_pixel_set(surface, point.x + i, point.y, color);
	}
	else
	{
		i = 1;
		while (--i > length)
			libui_pixel_set(surface, point.x + i, point.y, color);
	}
	return (0);
}

int	libui_pixel_draw_horizontal_line_atomic(SDL_Surface *surface,
	t_libui_pixel_coord point, int length, Uint32 color)
{
	int	i;

	SDL_LockSurface(surface);
	if (length > 0)
	{
		i = -1;
		while (++i < length)
			libui_pixel_set(surface, point.x + i, point.y, color);
	}
	else
	{
		i = 1;
		while (--i > length)
			libui_pixel_set(surface, point.x + i, point.y, color);
	}
	SDL_UnlockSurface(surface);
	return (0);
}
