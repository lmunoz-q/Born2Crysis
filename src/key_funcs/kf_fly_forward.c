/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_fly_forward.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:19:31 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/14 18:29:30 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_fly_forward(void *param)
{
	t_e		*e;

	e = param;
	e->editor.editor_cam.pos = vec3vec3_substract(e->editor.editor_cam.pos, vec3scalar_multiply(e->editor.editor_cam.view_dir, 0.2));
}
