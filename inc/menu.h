/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:37:50 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/08 14:30:14 by tfernand         ###   ########.fr       */
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

void			launch_main_menu(t_e *e);
void			launch_editor_interface(t_e *e);

#endif
