/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_call_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:00:17 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 17:00:18 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_callback.h>

int	libui_call_back(t_libui_callback_holder *ch, SDL_Event *event)
{
	if (ch->filter == SDL_FIRSTEVENT || ch->filter == SDL_LASTEVENT
			|| ch->filter == event->type)
		return (ch->callback(event, ch->widget, ch->user_data));
	return (0);
}
