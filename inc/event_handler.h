/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:45:22 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/13 19:53:25 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HANDLER_H
# define EVENT_HANDLER_H

# include "mflib.h"
# include "libui.h"

# define KEY_AMOUNT		512
# define BUTTON_AMOUNT	12

typedef struct	s_key
{
	t_bool		active;
	t_bool		continuous;
	t_bool		toggle;
	void		*params;
	void        (*func)(void *);
}				t_key;

typedef struct	s_mouse
{
	t_vec2i		pos;
	double		front[3];
	t_vec2d		sensitivity;
	SDL_Window	*win;
}				t_mouse;

typedef struct	s_input_map
{
	t_key		keys[KEY_AMOUNT];
	t_key		buttons[BUTTON_AMOUNT];
	t_mouse		mouse;
}				t_input_map;

void			init_input_map(t_input_map *ip, SDL_Window *win);
void			handle_events(t_input_map	*ip);

void			handle_key_down(t_input_map *m, SDL_Event *event);
void			handle_key_up(t_input_map *m, SDL_Event *event);

t_key			gen_key(void (*func)(void *), void *param, t_bool continuous);

#endif
