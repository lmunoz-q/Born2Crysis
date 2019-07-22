/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 21:49:50 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/22 21:58:32 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void			render_player(t_player	*p, SDL_Surface *s, t_world *world, t_camera *cam)
{
	if (p->main_hand && p->main_hand->model)
		render_mesh(((t_object *)p->main_hand->model)->mesh, cam, s, &get_sector(p->sector, world)->lights);
}