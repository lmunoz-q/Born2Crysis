/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mesh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 23:43:13 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/07 14:02:04 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		render_mesh(t_mesh *mesh, t_camera *cam, SDL_Surface *surface)
{
	int			count;
	t_polygon	*p;

	p = get_polygon_buffer();
	count = model_to_world(mesh, cam->pos, p);
	world_to_view(p, count, cam->view_matrix);
	clip_against_plane(p, &count, (double [3]){0, 0, ZNEAR}, (double [3]){0, 0, 1});
}
