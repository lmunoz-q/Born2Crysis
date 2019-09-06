/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_preview_rotate_pitch.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:03:01 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/03 00:17:57 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void		kf_preview_rotate_pitch_r(void *param)
{
	t_e		*e;
	t_vec4d	rot;
	t_mat4d	tmp;

	e = param;
	if (!e->editor.item_placer)
		return ;
	if (e->editor.is_modified)
	{
		mat4_init(&tmp);
		e->editor.item_placer->matrix = mat4mat4_multiply(e->editor.
				item_placer->matrix, mat4_rotate_pitch(tmp, MOD_ROT_SPEED));
	}
	else
	{
		rot = quat_rotator((t_vec3d){{0, 1, 0}}, ROTATE_SPEED);
		e->editor.item_rotation = quat_multiply(rot, e->editor.item_rotation);
	}
}

void		kf_preview_rotate_pitch_l(void *param)
{
	t_e		*e;
	t_vec4d	rot;
	t_mat4d	tmp;

	e = param;
	if (!e->editor.item_placer)
		return ;
	if (e->editor.is_modified)
	{
		mat4_init(&tmp);
		e->editor.item_placer->matrix = mat4mat4_multiply(e->editor.
				item_placer->matrix, mat4_rotate_pitch(tmp, -MOD_ROT_SPEED));
	}
	else
	{
		rot = quat_rotator((t_vec3d){{0, 1, 0}}, -ROTATE_SPEED);
		e->editor.item_rotation = quat_multiply(rot, e->editor.item_rotation);
	}
}
