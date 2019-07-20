/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_set_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:50:03 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 19:52:35 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void				skybox_set_pos(t_object *skybox, double pos[3])
{
	mat4_init(skybox->mesh->matrix);
	mat4_translate(skybox->mesh->matrix, pos[0], pos[1], pos[2]);
	mat4_rotate_yaw(skybox->mesh->matrix, -90);
	mat4_scale(skybox->mesh->matrix, 2, 2, 2);
}
