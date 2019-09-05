/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_pixel_draw_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:26:50 by hmartzol          #+#    #+#             */
/*   Updated: 2019/03/05 20:26:52 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_pixel.h>

static inline void	draw_line_v(SDL_Surface *surface, t_libui_pixel_coord v[4],
	Uint32 c)
{
	int	d;

	d = v[2].x - (v[2].y >> 1);
	while (v[0].y != v[1].y)
	{
		if (d >= 0)
		{
			v[0].x += v[3].x;
			d -= v[2].y;
		}
		v[0].y += v[3].y;
		d += v[2].x;
		libui_pixel_set(surface, v[0].x, v[0].y, c);
	}
}

static inline void	draw_line_h(SDL_Surface *surface, t_libui_pixel_coord v[4],
	Uint32 c)
{
	int	d;

	d = v[2].y - (v[2].x >> 1);
	while (v[0].x != v[1].x)
	{
		if (d >= 0)
		{
			v[0].y += v[3].y;
			d -= v[2].x;
		}
		v[0].x += v[3].x;
		d += v[2].y;
		libui_pixel_set(surface, v[0].x, v[0].y, c);
	}
}

int					libui_pixel_draw_line(SDL_Surface *surface,
	t_libui_pixel_coord a, t_libui_pixel_coord b, Uint32 color)
{
	t_libui_pixel_coord	d;
	t_libui_pixel_coord	s;

	if (a.x == b.x || a.y == b.y)
	{
		if (a.x == b.x)
			libui_pixel_draw_vertical_line(surface, a, b.y - a.y, color);
		else if (a.y == b.y)
			libui_pixel_draw_horizontal_line(surface, a, b.x - a.x, color);
		return (0);
	}
	libui_pixel_set(surface, a.x, a.y, color);
	d = (t_libui_pixel_coord){b.x - a.x, b.y - a.y};
	s = (t_libui_pixel_coord){d.x < 0 ? -1 : 1, d.y < 0 ? -1 : 1};
	d = (t_libui_pixel_coord){d.x < 0 ? -d.x << 1 : d.x << 1,
				d.y < 0 ? -d.y << 1 : d.y << 1};
	if (d.x > d.y)
		draw_line_h(surface, (t_libui_pixel_coord[4]){a, b, d, s}, color);
	else
		draw_line_v(surface, (t_libui_pixel_coord[4]){a, b, d, s}, color);
	return (0);
}

int					libui_pixel_draw_line_atomic(SDL_Surface *surface,
	t_libui_pixel_coord a, t_libui_pixel_coord b, Uint32 color)
{
	t_libui_pixel_coord	d;
	t_libui_pixel_coord	s;

	SDL_LockSurface(surface);
	if (a.x == b.x || a.y == b.y)
	{
		if (a.x == b.x)
			libui_pixel_draw_vertical_line(surface, a, b.y - a.y, color);
		else if (a.y == b.y)
			libui_pixel_draw_horizontal_line(surface, a, b.x - a.x, color);
		SDL_UnlockSurface(surface);
		return (0);
	}
	libui_pixel_set(surface, a.x, a.y, color);
	d = (t_libui_pixel_coord){b.x - a.x, b.y - a.y};
	s = (t_libui_pixel_coord){d.x < 0 ? -1 : 1, d.y < 0 ? -1 : 1};
	d = (t_libui_pixel_coord){d.x < 0 ? -d.x << 1 : d.x << 1,
						d.y < 0 ? -d.y << 1 : d.y << 1};
	if (d.x > d.y)
		draw_line_h(surface, (t_libui_pixel_coord[4]){a, b, d, s}, color);
	else
		draw_line_v(surface, (t_libui_pixel_coord[4]){a, b, d, s}, color);
	SDL_UnlockSurface(surface);
	return (0);
}
