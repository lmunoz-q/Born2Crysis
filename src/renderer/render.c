/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 23:28:35 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/11 18:38:44 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		render(t_e *e)
{
	render_sector(get_sector(e->main_player.sector, &e->world), e->win, &e->camera);
	look_at(e->camera.pos, (double [3]){0, 0, 0}, (double [3]){0, -1, 0}, e->camera.view_matrix);
	libui_window_refresh(e->win);
}
