/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openworld_renderer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:50:39 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/27 16:47:09 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	openworld_mesh_render(t_mesh *mesh, t_camera *cam,
	SDL_Surface *surf, t_light_comp *lcomp)
{
	t_vec4d		pos;

	vec4_init(&pos);
	pos = mat4vec4_multiply(mesh->matrix, pos);
	if (vec3vec3_dist(pos.c3.vec3d, cam->pos) > ZFAR)
		return ;
	if (mesh->sector_id != (Uint32)-1)
		render_invisible_mesh(mesh, cam, surf, lcomp);
}

void		openworld_render(t_world *world, t_camera *cam, SDL_Surface *surf, int sector_id)
{
	Uint32	j;
	t_sector	*sector;

	if (!(sector = get_sector(sector_id, world)))
		return ;
	j = -1;
	while (++j < sector->meshnum)
		openworld_mesh_render(&sector->mesh[j], cam, surf,
			&sector->lights);
}
