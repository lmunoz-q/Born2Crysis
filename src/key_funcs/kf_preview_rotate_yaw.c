/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_preview_rotate_yaw.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 15:56:18 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/03 00:15:14 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void		kf_preview_rotate_yaw_r(void *param)
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
				item_placer->matrix, mat4_rotate_yaw(tmp, MOD_ROT_SPEED));
	}
	else
	{
		rot = quat_rotator((t_vec3d){{1, 0, 0}}, ROTATE_SPEED);
		e->editor.item_rotation = quat_multiply(rot, e->editor.item_rotation);
	}
}

void		kf_preview_rotate_yaw_l(void *param)
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
				item_placer->matrix, mat4_rotate_yaw(tmp, -MOD_ROT_SPEED));
	}
	else
	{
		rot = quat_rotator((t_vec3d){{1, 0, 0}}, -ROTATE_SPEED);
		e->editor.item_rotation = quat_multiply(rot, e->editor.item_rotation);
	}
}
