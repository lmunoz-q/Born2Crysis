/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_callback.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:45:51 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/27 15:32:38 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_CALLBACK_H
# define LIBUI_CALLBACK_H

# include <libui_typedef.h>

struct	s_libui_callback_holder
{
	t_libui_callback	*callback;
	SDL_EventType		filter;
	void				*user_data;
	t_libui_widget		*widget;
};

struct	s_libui_double_color
{
	unsigned int		first_color;
	unsigned int		second_color;
};

int		libui_call_back(t_libui_callback_holder *ch, SDL_Event *event);
int		libui_callback_hoverbutton(SDL_Event *event, t_libui_widget *widget,
									void *data);
int		libui_callback_toggle_bool(SDL_Event *event, t_libui_widget *widget,
									void *data);
int		libui_callback_print_message(SDL_Event *event, t_libui_widget *widget,
									void *data);

void	libui_callback_setpressed(t_libui_widget *widget,
				t_libui_callback *callback, SDL_EventType filter, void *data);
void	libui_callback_sethover(t_libui_widget *widget,
				t_libui_callback *callback, SDL_EventType filter, void *data);

void	libui_callback_received_keydown(t_libui_widget *widget, char *key);

#endif
