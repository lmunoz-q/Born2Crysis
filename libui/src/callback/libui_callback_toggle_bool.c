/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_callback_toggle_bool.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:43:12 by tfernand          #+#    #+#             */
/*   Updated: 2019/05/08 15:45:39 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int		libui_callback_toggle_bool(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	SDL_bool	*bl;

	(void)event;
	(void)widget;
	bl = (SDL_bool *)data;
	if (*bl == SDL_TRUE)
		*bl = SDL_FALSE;
	else
		*bl = SDL_TRUE;
	return (0);
}
