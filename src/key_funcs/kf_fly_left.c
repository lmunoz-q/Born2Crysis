/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_fly_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 11:56:19 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/18 11:58:43 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_fly_left(void *param)
{
	t_e		*e;

	e = param;
	e->editor.editor_cam.pos = vec3vec3_add(e->editor.editor_cam.pos, vec3scalar_multiply(vec3_normalize(vec3vec3_crossproduct(e->editor.editor_cam.view_dir, (t_vec3d){.a = {0, 1, 0}})), FLY_SPEED));
}