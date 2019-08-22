/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_set_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:50:03 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 20:46:21 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void				skybox_set_pos(t_mesh *skybox, t_vec3d pos)
{
	if (!skybox)
		return ;
	mat4_init(&skybox->matrix);
	skybox->matrix = mat4_translate(skybox->matrix, pos.a[0], pos.a[1], pos.a[2]);
	skybox->matrix = mat4_scale(skybox->matrix, 1000, 1000, 1000);
}
