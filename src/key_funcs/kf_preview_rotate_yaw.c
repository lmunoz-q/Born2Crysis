/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_preview_rotate_yaw.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 15:56:18 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/02 23:50:40 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void		kf_preview_rotate_yaw_r(void *param)
{
	t_e		*e;
	t_vec4d	rot;

	e = param;
	if (!e->editor.item_placer)
		return ;
	if (e->editor.is_modified)
	{
		e->editor.item_placer->matrix = mat4_translate(
			e->editor.item_placer->matrix, ROTATE_SPEED, 0, 0);
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

	e = param;
	if (!e->editor.item_placer)
		return ;
	if (e->editor.is_modified)
	{
		e->editor.item_placer->matrix = mat4_translate(
			e->editor.item_placer->matrix, -ROTATE_SPEED, 0, 0);
	}
	else
	{
		rot = quat_rotator((t_vec3d){{1, 0, 0}}, -ROTATE_SPEED);
		e->editor.item_rotation = quat_multiply(rot, e->editor.item_rotation);
	}
}
