/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widgets_new_widgets_surface.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:58:21 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/27 16:42:48 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_widgets.h>
#include <libui_surface.h>

int	libui_widgets_new_widgets_surface(SDL_Rect rect,
									t_libui_widgets_surface *out)
{
	out->x = rect.x;
	out->y = rect.y;
	out->surface = SDL_CreateRGBSurface(LIBUI_SURFACE_FLAGS, rect.w, rect.h,
		LIBUI_SURFACE_DEPTH, LIBUI_SURFACE_RED_MASK, LIBUI_SURFACE_GREEN_MASK,
		LIBUI_SURFACE_BLUE_MASK, LIBUI_SURFACE_ALPHA_MASK);
	if (out->surface == NULL)
		return (-1);
	if ((out->pixel_bound_widget = SDL_malloc(sizeof(t_libui_widget*)
		* rect.w * rect.h)) == NULL)
	{
		SDL_FreeSurface(out->surface);
		return (-1);
	}
	SDL_memset(out->pixel_bound_widget, 0,
		sizeof(t_libui_widget*) * rect.w * rect.h);
	SDL_memset(out->surface->pixels, 0, (size_t)rect.h * out->surface->pitch);
	out->widgets = NULL;
	out->next = NULL;
	out->previous = NULL;
	out->pressed = NULL;
	out->hovered = NULL;
	return (0);
}
