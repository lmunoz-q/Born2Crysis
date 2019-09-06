/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_mesh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 17:13:06 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/24 00:10:14 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

int			mesh_delete(t_mesh **meshes, int size, int index)
{
	t_mesh	*tmp;

	if (index >= size || !(*meshes))
		return (0);
	if (!(tmp = (t_mesh *)malloc(sizeof(t_mesh) * (size - 1))))
		return (0);
	if ((*meshes)[index].polygons)
		free((*meshes)[index].polygons);
	mf_memcpy(tmp, *meshes, sizeof(t_mesh) * index);
	mf_memcpy(&tmp[index], &(*meshes)[index + 1], sizeof(t_mesh)
	* (size - index - 1));
	free(*meshes);
	*meshes = tmp;
	return (1);
}
