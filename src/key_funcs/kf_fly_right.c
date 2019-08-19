/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_fly_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 12:05:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/18 12:05:29 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_fly_right(void *param)
{
	t_e		*e;

	e = param;
	e->editor.editor_cam.pos = vec3vec3_substract(e->editor.editor_cam.pos, vec3scalar_multiply(vec3_normalize(vec3vec3_crossproduct(e->editor.editor_cam.view_dir, (t_vec3d){.a = {0, 1, 0}})), FLY_SPEED));
}