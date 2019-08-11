/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object_preview.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 00:25:41 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/12 01:23:06 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		render_object_preview(t_object *obj, SDL_Surface *surf, t_vec2i size)
{
	t_light_comp	lcomp;
	t_camera		camera;

	lcomp.light_count = 0;
	lcomp.lights = NULL;
	vec3_clear(&camera.pos);
	generate_projection_matrix(&camera.projection_matrix, size);
	camera.view_matrix = look_at((t_vec3d){.a = {0, 0, 0}},
	(t_vec3d){.a = {0, 1, 0}}, (t_vec3d){.a = {0, -1, 0}});
	render_object(obj, &camera, surf, &lcomp);
}