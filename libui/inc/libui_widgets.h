/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widgets.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:37:32 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/01 19:48:14 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_WIDGETS_H
# define LIBUI_WIDGETS_H

# include <libui_typedef.h>
# include <libui_pixel.h>
# include <libui_callback.h>

/*
** {struct s_libui_widgets_surface *next; int x, y; SDL_Surface *surface;
** t_libui_widget **pixel_bound_widget, *widgets, *focused, *pressed}
** -
** structure that hold all widgets of a window or panel
** the surface is meant to be blited on the window surface after rendering
** pixel_bound_widget is a list of all pixels of the surface that are bound to
** a widget, ex: testing the pixel 10, 10 to see which widget uses it will
** do pixel_bound_widget[x + y * surface->w]
** the focused widget is the one with the highest priority for non mouse event
** the pressed just store a reference to the currently pressed widget (high
** priority for releease event)
** x, y are the coordinate at which the surface will be blited in the window
** surface (basically, the SDL_Rect used for bliting is {x, y, surface->w,
** surface->h}
*/

struct			s_libui_widgets_surface
{
	struct s_libui_widgets_surface	*next;
	struct s_libui_widgets_surface	*previous;
	int								x;
	int								y;
	SDL_Surface						*surface;
	t_libui_widget					**pixel_bound_widget;
	t_libui_widget					*widgets;
	t_libui_widget					*pressed;
	t_libui_widget					*hovered;
};

/*
** {t_libui_widgets_surface *ws;
** struct s_libui_widget *next, *prev_brother, *next_brother, *parent, *shilds;
** t_libui_widget_type type; union u_libui_widget_data data;
** int has_focus, is_hover, is_pressed, need_redraw;
** t_libui_callback_holder *on_press, *on_releas, *on_hover, *on_draw;
** int depth; SDL_Rect rect; SDL_Surface *texture;}
** -
*/

struct			s_libui_widget
{
	t_libui_widgets_surface			*ws;
	struct s_libui_widget			*next;
	struct s_libui_widget			*parent;
	struct s_libui_widget			*shilds;
	int								type;
	void							*data;
	unsigned int					has_focus : 1;
	unsigned int					is_hover : 1;
	unsigned int					is_pressed : 1;
	unsigned int					is_hiden : 1;
	unsigned int					need_redraw : 2;
	unsigned int					translucid : 1;
	t_libui_callback_holder			on_press;
	t_libui_callback_holder			on_release;
	t_libui_callback_holder			on_hover;
	t_libui_callback_holder			on_redraw;
	t_libui_key_callback			*on_key_pressed;
	t_libui_callback_holder			on_visibility_change;
	SDL_Rect						rect;
	SDL_Point						relative_pos;
	SDL_Surface						*texture;
};

int				libui_widgets_new_widgets_surface(SDL_Rect rect,
												t_libui_widgets_surface *out);

/*
** redraw widget only if they need to be (flag need_redraw and not hiden, if
** parent is redrawn, all shilds will be redrawn except hiden ones) then set
** the need_redraw flag to 0
** the default pixel type is transparent (for bliting purpose)
** note: this function does not access the window except if widgets have a
** on_readraw callback
*/

int				libui_widgets_draw(t_libui_widgets_surface *ws);

enum			e_libui_widget_add_flags
{
	LUI_WAF_NONE = 0,
	LUI_WAF_SHILD = 1,
	LUI_WAF_TRANSLUCID = 2
};

/*
** if flag LUI_WAF_SHILD and parent NULL, will get the first fully covered
** widget by the new widget and use it as the parent
** if flag LUI_WAF_TRANSLUCID is set and texture non NULL, the clicable area
** will depend on the oppacity of the texture
** note: widgets must be fully inside the widgets_surface, and to be shild,
** fully inside it's parent
*/

int				libui_widgets_add_widget(t_libui_widgets_surface *ws,
											t_libui_widget *widget,
											t_libui_widget_add_flags flags,
											t_libui_widget *parent);

/*
** internal function to set the clicable area of the widget based on visibility
** and transparency
*/

void			libui_widgets_set_clic_area(t_libui_widgets_surface *ws,
											t_libui_widget *w);

/*
** toggle visibility of the widget
** state = 1: visible, state = 0: hide
** inherit = 1: affect all shildrens, inherit = 0: only the current widget
**   (shildrens will still be updated)
** brothers = 1: affect all next brothers, brothers = 0: only the current widget
*/

void			libui_widget_set_visibility(t_libui_widget *widget,
											int state,
											int inherit,
											int brothers);

void			libui_widgets_draw_rec(SDL_Surface *surface, t_libui_widget *w);

void			libui_widgets_surface_destroy(t_libui_widgets_surface *ws);

#endif
