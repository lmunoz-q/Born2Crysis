/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_bool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:11:24 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/31 18:11:25 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom_nukem.h"
#include "menu.h"
#include <SDL2/SDL.h>

int		switch_bool(SDL_Event *event, t_libui_widget *widget, void *data)
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
