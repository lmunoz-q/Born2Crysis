/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_preview_rotate_roll.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:08:56 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/02 23:54:56 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void		kf_preview_rotate_roll_r(void *param)
{
	t_e		*e;
	t_vec4d	rot;

	e = param;
	if (!e->editor.item_placer)
		return ;
	if (e->editor.is_modified)
	{
		e->editor.item_placer->matrix = mat4_translate(
			e->editor.item_placer->matrix, 0, ROTATE_SPEED, 0);
	}
	else
	{
		rot = quat_rotator((t_vec3d){{0, 0, 1}}, ROTATE_SPEED);
		e->editor.item_rotation = quat_multiply(rot, e->editor.item_rotation);
	}
}

void		kf_preview_rotate_roll_l(void *param)
{
	t_e		*e;
	t_vec4d	rot;

	e = param;
	if (!e->editor.item_placer)
		return ;
	if (e->editor.is_modified)
	{
		e->editor.item_placer->matrix = mat4_translate(
			e->editor.item_placer->matrix, 0, -ROTATE_SPEED, 0);
	}
	else
	{
		rot = quat_rotator((t_vec3d){{0, 0, 1}}, -ROTATE_SPEED);
		e->editor.item_rotation = quat_multiply(rot, e->editor.item_rotation);
	}
}
