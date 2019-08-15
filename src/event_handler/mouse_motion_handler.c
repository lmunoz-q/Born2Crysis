/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_motion_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:37:18 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/14 17:56:29 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handler.h"

void		handle_mouse_motion(t_mouse	*mouse, SDL_Event *event)
{
	int x;
	int y;

	(void)event;
	SDL_GetRelativeMouseState(&x, &y);
	mouse->pos.n.x += x * mouse->sensitivity.n.x;
	mouse->pos.n.y += y * mouse->sensitivity.n.y;
	if (mouse->pos.n.y > 89)
		mouse->pos.n.y = 89;
	if (mouse->pos.n.y < -89)
		mouse->pos.n.y = -89;
	mouse->front.n.x = cos(mouse->pos.n.x * M_PI / 180.0) * cos(mouse->pos.n.y * M_PI / 180.0);
	mouse->front.n.y = sin(mouse->pos.n.y * M_PI / 180.0);
	mouse->front.n.z = sin(mouse->pos.n.x * M_PI / 180.0) * cos(mouse->pos.n.y * M_PI / 180.0);
	mouse->front = vec3_normalize(mouse->front);
}
