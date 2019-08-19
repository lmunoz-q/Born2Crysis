/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mesh_preview.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 15:01:26 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/19 21:44:19 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		render_preview(t_mesh *mesh, SDL_Surface *surf, t_vec2i size)
{
	t_camera		camera;
	
	vec3_clear(&camera.pos);
	mf_memset(surf->pixels, 0, surf->w * surf->h * sizeof(Uint32));
	camera.pos.n.z = mesh->radius + 15;
	camera.view_dir = (t_vec3d){.a = {0, 0, camera.pos.n.z + 1.0}};
	mesh->matrix = mat4_rotate_pitch(mesh->matrix, 1);
	generate_projection_matrix(&camera.projection_matrix, size);
	mat4_init(&camera.view_matrix);
	camera.view_matrix = look_at(camera.pos,
	camera.view_dir, (t_vec3d){.a = {0, -1, 0}});
	render_mesh(mesh, &camera, surf, NULL);
}