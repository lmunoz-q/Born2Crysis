/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_set_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:50:03 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/22 19:31:12 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void				skybox_set_pos(t_object *skybox, t_vec3d pos)
{
	mat4_init(&skybox->mesh->matrix);
	skybox->mesh->matrix = mat4_translate(skybox->mesh->matrix, pos.a[0], pos.a[1], pos.a[2]);
	//mat4_rotate_yaw(skybox->mesh->matrix, -90);
	skybox->mesh->matrix = mat4_scale(skybox->mesh->matrix, 1000, 1000, 1000);
}
