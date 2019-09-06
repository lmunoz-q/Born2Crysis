/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_change_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:39:58 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 19:46:31 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	mesh_change_texture(t_mesh *mesh, int32_t id)
{
	int32_t i;

	if (!mesh || id == -1)
		return ;
	i = -1;
	while (++i < mesh->polygonnum)
	{
		mesh->polygons[i].tex_id = id;
	}
}
