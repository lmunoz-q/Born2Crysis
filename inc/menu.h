/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:37:50 by tfernand          #+#    #+#             */
/*   Updated: 2019/05/08 14:17:34 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "typedefs.h"
# include "doom_nukem.h"

typedef enum		e_state
{
	B2C_STATE_MAIN_MENU, //play, edit, options, credit, exit
	B2C_STATE_PLAY_MENU, //new game, load game, multiplayer, return
	B2C_STATE_NEW_GAME_MENU, //selector, start, return
	B2C_STATE_LOAD_MENU, //load, delete, duplicate, return
	B2C_STATE_MULTIPLAYER_MENU, //host (select mode/nb players), join, direct connect, return
	B2C_STATE_IN_GAME_MENU, //continue, save, load, options, quit
	B2C_STATE_OPTIONS_MENU, //music/sounds, keybinds, mouse, name, avatar
	B2C_STATE_EDITOR, // editor
	B2C_STATE_CREDITS, // us
	B2C_STATE_PLAYING //refer to hosttype and gametype
}					t_state;

typedef struct	s_double_color
{
	int			first_color;
	int			second_color;
}				t_double_color;

void			launch_main_menu(t_e *e);

#endif
