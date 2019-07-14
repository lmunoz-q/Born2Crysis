/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_motion_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:37:18 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/13 21:53:13 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handler.h"

void		handle_mouse_motion(t_mouse	*mouse, SDL_Event *event)
{
	int x;
	int y;

	(void)event;
	SDL_GetRelativeMouseState(&x, &y);
	mouse->pos.x += x * mouse->sensitivity.x;
	mouse->pos.y += y * mouse->sensitivity.y;
	if (mouse->pos.y > 89)
		mouse->pos.y = 89;
	if (mouse->pos.y < -89)
		mouse->pos.y = -89;
	mouse->front[0] = cos(mouse->pos.x * M_PI / 180.0) * cos(mouse->pos.y * M_PI / 180.0);
	mouse->front[1] = sin(mouse->pos.y * M_PI / 180.0);
	mouse->front[2] = sin(mouse->pos.x * M_PI / 180.0) * cos(mouse->pos.y * M_PI / 180.0);
	vec3_normalize_s(mouse->front);
}
