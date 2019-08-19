/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_preview_rotate_pitch.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:03:01 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/18 16:04:17 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void		kf_preview_rotate_pitch_r(void *param)
{
	t_e *e;

	e = param;
	e->editor.item_rotation_mat = mat4_rotate_pitch(e->editor.item_rotation_mat, ROTATE_SPEED);
}

void		kf_preview_rotate_pitch_l(void *param)
{
	t_e *e;

	e = param;
	e->editor.item_rotation_mat = mat4_rotate_pitch(e->editor.item_rotation_mat, -ROTATE_SPEED);
}