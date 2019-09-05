/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_window.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:31:50 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/27 16:40:51 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUIMP_LIBUI_WINDOW_H
# define GUIMP_LIBUI_WINDOW_H

# include <libui_typedef.h>

# define LUI_DEFAULT_REFRESH_RATE 60
# define LUI_DEAULT_WINDOW_WIDTH 1920
# define LUI_DEFAULT_WINDOW_HEIGHT 1080
# define LUI_DEFAULT_WINDOW_NAME ""

struct						s_libui_window_constructor
{
	SDL_Rect	rect;
	const char	*name;
	Uint32		winow_flags;
	Uint32		renderer_flags;
	int			refresh_rate;
	Uint32		surface_flags;
	int			depth;
	Uint32		red_mask;
	Uint32		green_mask;
	Uint32		blue_mask;
	Uint32		alpha_mask;
};

struct						s_libui_window
{
	t_libui_window_constructor	constructor;
	t_libui_window				*parent;
	t_libui_window				*shild;
	t_libui_window				*prev;
	t_libui_window				*next;
	SDL_Window					*ptr;
	SDL_Renderer				*renderer;
	SDL_Surface					*surface;
	SDL_mutex					*mutex;
	t_libui_widgets_surface		*widgets_surface;
	t_libui_widget				*focused_widget;
	int							refresh_rate;
	int							fps;
	int							last_tick;
	int							frame;
};

t_libui_window_constructor	libui_window_default_constructor(void);
void						libui_window_delete(t_libui_window *win);
t_libui_window				*libui_window_create(
								t_libui_window_constructor constructor,
								t_libui_window *parent,
								t_libui_window *prev,
								t_libui_window *next);
int							libui_window_process_fps(
								t_libui_window *win);
int							libui_window_refresh(
								t_libui_window *win);
void						libui_window_clear(
								t_libui_window *win);
void						libui_window_clear_atomic(
								t_libui_window *win);
int							libui_window_title(
								t_libui_window *win,
								const char *format,
								...) __attribute__((format(printf,2,3)));
int							libui_resize_window_surface(t_libui_window *win,
								int w, int h);
void						libui_window_update(t_libui_window *win);

#endif
