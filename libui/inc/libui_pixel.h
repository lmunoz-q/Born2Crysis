/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_pixel.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:31:42 by hmartzol          #+#    #+#             */
/*   Updated: 2019/03/05 18:32:38 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_PIXEL_H
# define LIBUI_PIXEL_H

# include <libui_typedef.h>
# include <libui_maths.h>

struct									s_libui_pixel_color_big
{
	Uint8				a;
	Uint8				r;
	Uint8				g;
	Uint8				b;
};

struct									s_libui_pixel_color_little
{
	Uint8				r;
	Uint8				b;
	Uint8				g;
	Uint8				a;
};

# if SDL_BYTEORDER == SDL_LIL_ENDIAN
#  define __S_LIBUI_PIXEL_COLOR struct s_libui_pixel_color_little
# else
#  define __S_LIBUI_PIXEL_COLOR struct s_libui_pixel_color_big
# endif

union									u_libui_pixel_color
{
	Uint32								u32;
	__S_LIBUI_PIXEL_COLOR				c;
};

# undef __S_LIBUI_PIXEL_COLOR

struct									s_libui_pixel
{
	t_libui_pixel_coord					coord;
	t_libui_pixel_color					color;
};

Uint32									libui_pixel_get(
													SDL_Surface *surface,
													int x,
													int y);
Uint32									libui_pixel_get_atomic(
													SDL_Surface *surface,
													int x,
													int y);
int										libui_pixel_set(
													SDL_Surface *surface,
													int x,
													int y,
													Uint32 color);
int										libui_pixel_set_atomic(
													SDL_Surface *surface,
													int x,
													int y,
													Uint32 color);
int										libui_pixel_draw_horizontal_line(
													SDL_Surface *surface,
													t_libui_pixel_coord point,
													int length,
													Uint32 color);
int										libui_pixel_draw_horizontal_line_atomic(
													SDL_Surface *surface,
													t_libui_pixel_coord point,
													int length,
													Uint32 color);
int										libui_pixel_draw_vertical_line(
													SDL_Surface *surface,
													t_libui_pixel_coord point,
													int length,
													Uint32 color);
int										libui_pixel_draw_vertical_line_atomic(
													SDL_Surface *surface,
													t_libui_pixel_coord point,
													int length,
													Uint32 color);
int										libui_pixel_draw_line(
													SDL_Surface *surface,
													t_libui_pixel_coord a,
													t_libui_pixel_coord b,
													Uint32 color);
int										libui_pixel_draw_line_atomic(
													SDL_Surface *surface,
													t_libui_pixel_coord a,
													t_libui_pixel_coord b,
													Uint32 color);
t_libui_pixel_coord						libui_pixel_coord_centered(
													SDL_Surface *surface,
													double x,
													double y);
int										libui_pixel_draw(
													SDL_Surface *surface,
													int x,
													int y,
													Uint32 color);
int										libui_pixel_draw_atomic(
													SDL_Surface *surface,
													int x,
													int y,
													Uint32 color);

#endif
