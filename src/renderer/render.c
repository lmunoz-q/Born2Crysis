/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 23:28:35 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/13 20:11:56 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		render(t_e *e)
{
	libui_window_clear(e->win);
	look_at(e->camera.pos, (double [3]){0, 0, 0}, (double [3]){0, 1, 0}, e->camera.view_matrix);
	render_sector(get_sector(e->main_player.sector, &e->world), e->win, &e->camera);
	libui_window_refresh(e->win);
}
