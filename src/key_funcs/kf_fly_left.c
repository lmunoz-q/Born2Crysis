/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_fly_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 11:56:19 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/03 00:07:01 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_fly_left(void *param)
{
	t_e		*e;

	e = param;
	if (e->editor.item_placer && e->editor.is_modified && e->input_map.keys[SDL_SCANCODE_LSHIFT].active)
	{
		e->editor.item_placer->matrix = mat4_translate(
			e->editor.item_placer->matrix, -ROTATE_SPEED, 0, 0);
	}
	else
	{
		e->editor.editor_cam.pos = vec3vec3_add(e->editor.editor_cam.pos,
			vec3scalar_multiply(vec3_normalize(vec3vec3_crossproduct(e->editor.
			editor_cam.view_dir, (t_vec3d){.a = {0, 1, 0}})), FLY_SPEED));
	}
}
