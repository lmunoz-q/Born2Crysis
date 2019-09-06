/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_motion_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:37:18 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/21 18:36:43 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

void		handle_mouse_motion(t_mouse *mouse, SDL_Event *event, t_e *e)
{
	int		x;
	int		y;

	if (e->editor_running && e->editor.is_in_view == FALSE)
		return ;
	(void)event;
	SDL_GetRelativeMouseState(&x, &y);
	mouse->pos.n.x += (double)x * mouse->sensitivity.n.x;
	mouse->pos.n.y += (double)y * mouse->sensitivity.n.y;
	if (mouse->pos.n.y > 89)
		mouse->pos.n.y = 89;
	if (mouse->pos.n.y < -89)
		mouse->pos.n.y = -89;
	mouse->front.n.x = cos(mouse->pos.n.x * M_PI / 180.0)
		* cos(mouse->pos.n.y * M_PI / 180.0);
	mouse->front.n.y = sin(mouse->pos.n.y * M_PI / 180.0);
	mouse->front.n.z = sin(mouse->pos.n.x * M_PI / 180.0)
		* cos(mouse->pos.n.y * M_PI / 180.0);
	mouse->front = vec3_normalize(mouse->front);
}
