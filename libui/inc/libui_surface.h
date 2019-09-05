/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_surface.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:31:32 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/29 22:29:47 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_SURFACE_H
# define LIBUI_SURFACE_H

# include <libui_typedef.h>

# define LIBUI_SURFACE_FLAGS SDL_SWSURFACE
# define LIBUI_SURFACE_DEPTH 32
# define LIBUI_SURFACE_RED_MASK ((Uint32)0xFF0000)
# define LIBUI_SURFACE_GREEN_MASK ((Uint32)0xFF00)
# define LIBUI_SURFACE_BLUE_MASK ((Uint32)0xFF)
# define LIBUI_SURFACE_ALPHA_MASK ((Uint32)0xFF000000)

SDL_Surface	*libui_surface_image_load_32argb(const char *path,
												int width,
												int height);

SDL_Surface	*libui_surface_image_load_32argb_scale(const char *path,
												double width,
												double height);

#endif
