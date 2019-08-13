/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object_preview.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 00:25:41 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/13 17:03:24 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		render_object_preview(t_object *obj, SDL_Surface *surf, t_vec2i size)
{
	t_camera		camera;

	vec3_clear(&camera.pos);
	mf_memset(surf->pixels, 0, surf->w * surf->h * sizeof(Uint32));
	camera.pos.n.z = 8;
	camera.pos.n.y = 2;
	camera.view_dir = (t_vec3d){.a = {0, 2, 9}};
	obj->mesh[0].matrix = mat4_rotate_pitch(obj->mesh[0].matrix, 1);
	generate_projection_matrix(&camera.projection_matrix, size);
	mat4_init(&camera.view_matrix);
	camera.view_matrix = look_at(camera.pos,
	camera.view_dir, (t_vec3d){.a = {0, -1, 0}});
	render_object(obj, &camera, surf, NULL);
}