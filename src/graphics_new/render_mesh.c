/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mesh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 23:43:13 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/11 01:19:35 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		render_mesh(t_mesh *mesh, t_camera *cam, SDL_Surface *surface)
{
	int			count;
	t_polygon	*p;

	p = get_polygon_buffer();
	count = model_to_world(mesh, cam->pos, p);
	printf("1: x: %f, y: %f, z: %f, w: %f\n", p[0].v01[0], p[0].v01[1], p[0].v01[2], p[0].v01[3]);
	world_to_view(p, count, cam->view_matrix);
	printf("2: x: %f, y: %f, z: %f, w: %f\n", p[0].v01[0], p[0].v01[1], p[0].v01[2], p[0].v01[3]);
	count = clip_against_plane(p, count, (double [3]){0, 0, ZNEAR}, (double [3]){0, 0, 1});
	printf("3: x: %f, y: %f, z: %f, w: %f\n", p[0].v01[0], p[0].v01[1], p[0].v01[2], p[0].v01[3]);
	view_to_projection(p, count, cam->projection_matrix, surface);
	printf("4: x: %f, y: %f, z: %f, w: %f\n", p[0].v01[0], p[0].v01[1], p[0].v01[2], p[0].v01[3]);
	//count = clip_screen(p, count, surface->w, surface->h);
	rasterize(p, count, surface);
}
