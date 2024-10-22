/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_fly_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 12:05:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/06 13:10:18 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_fly_right(void *param)
{
	t_e		*e;

	e = param;
	if (e->editor.item_placer && e->editor.is_modified && e->input_map.
	keys[SDL_SCANCODE_LSHIFT].active)
	{
		e->editor.item_placer->matrix = mat4_translate(
			e->editor.item_placer->matrix, ROTATE_SPEED, 0, 0);
		if (e->editor.item_placer->walls && e->editor.item_placer->nb_walls)
		{
			mesh_delete_physics(e->editor.item_placer);
			mesh_add_physics(e->editor.item_placer,
			(e->editor.wall_friction_is_auto)
			? -1 : e->editor.wall_friction);
		}
	}
	else
	{
		e->editor.editor_cam.pos = vec3vec3_substract(e->editor.editor_cam.pos,
			vec3scalar_multiply(vec3_normalize(vec3vec3_crossproduct(e->editor.
			editor_cam.view_dir, (t_vec3d){.a = {0, 1, 0}})), FLY_SPEED));
	}
}
