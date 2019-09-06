/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 17:24:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/06 10:20:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_mesh		*mesh_copy(t_mesh *mesh)
{
	t_mesh *new_mesh;

	if (!(new_mesh = (t_mesh *)malloc(sizeof(t_mesh))))
		return (NULL);
	mf_memcpy(new_mesh, mesh, sizeof(t_mesh));
	if (!(new_mesh->polygons = (t_polygon *)malloc(sizeof(t_polygon)
		* new_mesh->polygonnum)))
		return (NULL);
	mf_memcpy(new_mesh->polygons, mesh->polygons, sizeof(t_polygon)
	* mesh->polygonnum);
	new_mesh->nb_walls = 0;
	new_mesh->walls = NULL;
	return (new_mesh);
}
