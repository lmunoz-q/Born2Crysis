/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_wireframe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 10:34:43 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/03 10:50:54 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	rasterize_wireframe(t_polygon *p, int count, SDL_Surface *surface,
							Uint32 color)
{
	int					i;

	i = -1;
	while (++i < count)
	{
		if (p[i].tex_id == -1)
			continue ;
		libui_pixel_draw_line(surface,
		(t_int2){.x = p[i].v01.a[0], .y = p[i].v01.a[1]},
		(t_int2){.x = p[i].v12.a[0], .y = p[i].v12.a[1]}, color);
		libui_pixel_draw_line(surface,
		(t_int2){.x = p[i].v12.a[0], .y = p[i].v12.a[1]},
		(t_int2){.x = p[i].v20.a[0], .y = p[i].v20.a[1]}, color);
		libui_pixel_draw_line(surface,
		(t_int2){.x = p[i].v20.a[0], .y = p[i].v20.a[1]},
		(t_int2){.x = p[i].v01.a[0], .y = p[i].v01.a[1]}, color);
	}
}