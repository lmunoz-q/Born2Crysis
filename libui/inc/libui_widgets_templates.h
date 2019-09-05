/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widgets_templates.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:37:32 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/01 18:41:28 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_WIDGETS_TEMPLATES_H
# define LIBUI_WIDGETS_TEMPLATES_H

# include <libui_widgets.h>
# include <SDL2/SDL_ttf.h>
# include <libui_callback.h>
# include <libui_typedef.h>

# define LIBUI_LABEL_DEFAULT_COLOR 0xffffffff
# define LIBUI_CLEAR_DEFAULT_COLOR 0x00000000

# define LIBUI_WIDGET_PROGRESSBAR_DEFAULT_BACKCOLOR 0xff444444
# define LIBUI_WIDGET_PROGRESSBAR_DEFAULT_FRONTCOLOR 0xffcccccc

# define LIBUI_INPUT_TEXT_MAX_SIZE 50

enum			e_libui_widget_type
{
	LUI_WT_UNDEFINED = 0,
	LUI_WT_IMAGE,
	LUI_WT_ANIMATION,
	LUI_WT_BUTTON,
	LUI_WT_CHECK,
	LUI_WT_TEXT,
	LUI_WT_TEXT_EDIT,
	LUI_WT_RADIO,
	LUI_WT_SLIDER,
	LUI_WT_PROGRESSBAR,
	LUI_WT_MENU,
	LUI_WT_COMPOSITE,
	LUI_WT_ACTIVABLE,
	LUI_WT_INPUTTEXT,
	LUI_WT_TEXT_BUTTON
};

enum			e_libui_widget_slider_freedom
{
	LUI_WSF_NONE = 0,
	LUI_WSF_HORIZONTAL = 1,
	LUI_WSF_VERTICAL = 2,
	LUI_WSF_ALL = 3
};

struct			s_libui_widget_checkbox
{
	int								state;
	int								(*on_state_change)(t_libui_widget *, int,
														void *);
	void							*user_data;
};

/*
** radio are meant to be able to find all other radio of the same group
** the neighboor is used to make a circular linked list of radio
*/

struct			s_libui_widget_radio
{
	int								state;
	t_libui_widget					*neighboor;
};

struct			s_libui_widget_animation
{
	t_libui_animation				*ptr;
};

struct			s_libui_widget_text
{
	char							*ptr;
	size_t							len;
	TTF_Font						*font;
	SDL_Color						color;
};

struct			s_libui_widget_progressbar
{
	int						back_color;
	int						front_color;
	double					value;
	int						value_min;
	int						value_max;
	int						value_current;
};

struct			s_libui_widget_menu
{
	unsigned int			option_height;
	unsigned int			current_height;
	t_libui_widgets_surface	ws;
	t_libui_widget			selecteur;
	t_libui_widget			unselecteur;
};

struct			s_libui_menu_constructor
{
	t_libui_widgets_surface		*ws;
	t_libui_widget				*parent;
	SDL_Rect					rect;
	SDL_Rect					label_rect;
	SDL_Rect					selecteur_rect;
	char						*text;
	TTF_Font					*font;
	const t_libui_double_color	*theme;
	unsigned int				options_number;
	unsigned int				option_height;
};

struct			s_libui_textbutton_constructor
{
	t_libui_widgets_surface		*ws;
	t_libui_widget				*parent;
	SDL_Rect					rect;
	SDL_Rect					label_rect;
	char						*text;
	TTF_Font					*font;
	const t_libui_double_color	*theme;
};

struct			s_libui_inputtext_constructor
{
	t_libui_widgets_surface		*ws;
	t_libui_widget				*parent;
	SDL_Rect					rect;
	SDL_Rect					label_rect;
	TTF_Font					*font;
	char						*text;
	unsigned int				text_max_len;
	SDL_Color					font_color;
	int							back_color;
};

struct			s_libui_inputtext
{
	char						*text;
	unsigned int				text_len;
	unsigned int				text_max_len;
};

struct			s_libui_widget_text_edit
{
	char							*ptr;
	size_t							cursor_line;
	size_t							cursor_column;
	size_t							cursor_pos;
	size_t							len;
};

/*
** default value for an empty widget
*/

t_libui_widget	libui_widgets_templates_null(void);

/*
** basic rectangle to attach events and sub-widgets
** base of most composites (ex: slider)
*/

int				libui_widgets_templates_rect(t_libui_widget *out,
												SDL_Rect rect);

/*
** simple rect with an image
*/

int				libui_widgets_templates_image(t_libui_widget *out,
												const char *path,
												SDL_Rect rect);

/*
** rect with a surface meant to be redrawn at each call of libui_widgets_draw
** cb will be called before each redraw
*/

int				libui_widgets_templates_animation(t_libui_widget *out,
													SDL_Rect rect,
													t_libui_callback *cb,
													void *user_data);

#endif
