/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_capture_mouse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 16:07:45 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/15 16:26:48 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

int	toggle_capture_mouse(SDL_Event *event, t_libui_widget *widget, void *data)
{
	(void)event;
	(void)widget;
	if (SDL_GetRelativeMouseMode())
	{
		SDL_SetWindowGrab((SDL_Window *)data, SDL_FALSE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
	else
	{
		SDL_SetWindowGrab((SDL_Window *)data, SDL_TRUE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	return (0);
}
