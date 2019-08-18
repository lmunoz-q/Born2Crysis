/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_preview_rotate_yaw.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 15:56:18 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/18 16:04:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void		kf_preview_rotate_yaw_r(void *param)
{
	t_e *e;

	e = param;
	e->editor.item_rotation_mat = mat4_rotate_yaw(e->editor.item_rotation_mat, ROTATE_SPEED);
}

void		kf_preview_rotate_yaw_l(void *param)
{
	t_e *e;

	e = param;
	e->editor.item_rotation_mat = mat4_rotate_yaw(e->editor.item_rotation_mat, -ROTATE_SPEED);
}