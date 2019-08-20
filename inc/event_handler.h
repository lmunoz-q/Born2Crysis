/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:45:22 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/21 01:46:11 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HANDLER_H
# define EVENT_HANDLER_H

# include "mflib.h"
# include "libui.h"

# define KEY_AMOUNT		1024
# define BUTTON_AMOUNT	24

# define KF_MOUSEWHEEL  13
# define KF_FILEDROP 1023
# define DEFAULT_MOUSE_SENSITIVITY 0.2

typedef struct	s_key
{
	t_bool		active;
	t_bool		continuous;
	t_bool		toggle;
	void		*params;
	void		(*func)(void *);
}				t_key;

typedef struct	s_mouse
{
	t_vec2d			pos;
	t_vec3d			front;
	t_vec2d			sensitivity;
	t_vec2i			wheel_scrol;
	t_libui_window	*win;
}				t_mouse;

typedef struct	s_input_map
{
	t_key		keys[KEY_AMOUNT];
	t_key		buttons[BUTTON_AMOUNT];
	t_mouse		mouse;
	char		*drop_file_path;
}				t_input_map;

void			init_input_map(t_input_map *ip, t_libui_window *win);
void			handle_events(t_input_map	*ip);
void			handle_mouse_motion(t_mouse	*mouse, SDL_Event *event);

void			handle_key_down(t_input_map *m, SDL_Event *event);
void			handle_key_up(t_input_map *m, SDL_Event *event);

t_key			gen_key(void (*func)(void *), void *param, t_bool continuous);

#endif
