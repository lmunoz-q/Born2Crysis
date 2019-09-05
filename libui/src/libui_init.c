/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:25:47 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/27 14:46:39 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui.h>

int	libui_init(void)
{
	t_libui_env	*env;
	int			r;

	if ((r = SDL_Init(SDL_INIT_EVERYTHING)))
		return (r);
	if ((r = TTF_Init()))
		return (r);
	env = libui_env();
	env->discarded_event = SDL_RegisterEvents(2);
	env->widget_redraw_event = env->discarded_event + 1;
	SDL_StartTextInput();
	return (r);
}
