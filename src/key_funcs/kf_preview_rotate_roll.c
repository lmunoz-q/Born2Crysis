/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_preview_rotate_roll.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:08:56 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/18 16:09:15 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void		kf_preview_rotate_roll_r(void *param)
{
	t_e *e;

	e = param;
	e->editor.item_rotation_mat = mat4_rotate_roll(e->editor.item_rotation_mat, ROTATE_SPEED);
}

void		kf_preview_rotate_roll_l(void *param)
{
	t_e *e;

	e = param;
	e->editor.item_rotation_mat = mat4_rotate_roll(e->editor.item_rotation_mat, -ROTATE_SPEED);
}