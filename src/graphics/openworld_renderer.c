/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openworld_renderer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:50:39 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/13 21:00:01 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	openworld_mesh_render(t_mesh *mesh, t_camera *cam, SDL_Surface *surf, t_light_comp *lcomp)
{
	t_vec4d		pos;

	vec4_init(&pos);
	pos = mat4vec4_multiply(mesh->matrix, pos);
	if (vec3vec3_dist(pos.c3.vec3d, cam->pos) > ZFAR)
		return ;
	render_mesh(mesh, cam, surf, lcomp);
}

static void	openworld_object_render(t_object *object, t_camera *cam, SDL_Surface *surf, t_light_comp *lcomp)
{
	int i;

	i = -1;
	while (++i < object->sub_object_num)
	{
		object->sub_object[i].matrix = mat4mat4_multiply(object->sub_object[i].matrix_o, object->matrix_o);
		openworld_object_render(&object->sub_object[i], cam, surf, lcomp);
	}
	i = -1;
	while (++i < object->meshnum)
	{
		openworld_mesh_render(&object->mesh[i], cam, surf, lcomp);
	}
}

void		openworld_render(t_world *world, t_camera *cam, SDL_Surface *surf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < world->sectornum)
	{
		j = -1;
		while (++j < world->sectors[i].meshnum)
			openworld_mesh_render(&world->sectors[i].mesh[j], cam, surf, &world->sectors[i].lights);
		j = -1;
		while (++j < world->sectors[i].objectnum)
			openworld_object_render(&world->sectors[i].objects[j], cam, surf, &world->sectors[i].lights);
	}
}