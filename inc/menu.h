/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:37:50 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/31 18:45:56 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "typedefs.h"
# include "doom_nukem.h"

typedef enum	e_state
{
	B2C_STATE_MAIN_MENU,
	B2C_STATE_PLAY_MENU,
	B2C_STATE_NEW_GAME_MENU,
	B2C_STATE_LOAD_MENU,
	B2C_STATE_MULTIPLAYER_MENU,
	B2C_STATE_IN_GAME_MENU,
	B2C_STATE_OPTIONS_MENU,
	B2C_STATE_EDITOR,
	B2C_STATE_CREDITS,
	B2C_STATE_PLAYING
}				t_state;

typedef struct	s_double_color
{
	int			first_color;
	int			second_color;
}				t_double_color;

typedef struct s_menu_content
{
	TTF_Font					*font;
	t_libui_widget				widget_buttonplay;
	t_libui_widget				widget_buttoneditor;
	t_libui_widget				widget_buttonquitter;
	SDL_bool					win_running;
	SDL_bool					editor_running;
	SDL_bool					game_running;
	t_libui_double_color		theme;
}				t_menu_content;


void			launch_main_menu(t_e *e);
void			launch_editor_interface(t_e *e);
int				change_color(SDL_Event *event, t_libui_widget *widget, void *d);
int				switch_bool(SDL_Event *event, t_libui_widget *widget, void *data);
int				add_editorbutton(t_e *e, t_menu_content *menu_content);
int				add_quitbutton(t_e *e, t_menu_content *menu_content);
int				add_playbutton(t_e *e, t_menu_content *menu_content);

#endif
