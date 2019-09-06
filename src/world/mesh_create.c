/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:49:01 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 19:22:05 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

static void	i_boucle(t_mesh *mesh, t_vec2i size, int *t, t_vec2i *i)
{
	mesh->polygons[++*t].tex_id = 1;
	mesh->polygons[*t].transparency = 0;
	mesh->polygons[*t].v01 = (t_vec4d){.a
	= {i->n.x - (size.n.x / 2), 0, i->n.y - (size.n.y / 2), 1}};
	mesh->polygons[*t].v12 = (t_vec4d){.a
	= {i->n.x - (size.n.x / 2) + 1, 0, i->n.y - (size.n.y / 2), 1}};
	mesh->polygons[*t].v20 = (t_vec4d){.a
	= {i->n.x - (size.n.x / 2) + 1, 0, i->n.y - (size.n.y / 2) + 1, 1}};
	mesh->polygons[++*t].tex_id = 1;
	mesh->polygons[*t].transparency = 0;
	mesh->polygons[*t].v01 = (t_vec4d){.a
	= {i->n.x - (size.n.x / 2), 0, i->n.y - (size.n.y / 2), 1}};
	mesh->polygons[*t].v12 = (t_vec4d){.a
	= {i->n.x - (size.n.x / 2) + 1, 0, i->n.y - (size.n.y / 2) + 1, 1}};
	mesh->polygons[*t].v20 = (t_vec4d){.a
	= {i->n.x - (size.n.x / 2), 0, i->n.y - (size.n.y / 2) + 1, 1}};
}

static void	init_mesh(t_mesh *mesh, t_vec2i size)
{
	int		t;
	t_vec2i	i;

	t = -1;
	i.n.y = -1;
	while (++i.n.y < size.n.y - 1)
	{
		i.n.x = -1;
		while (++i.n.x < size.n.x - 1)
			i_boucle(mesh, size, &t, &i);
	}
}

t_mesh		*mesh_create(t_vec2i size)
{
	t_mesh	*mesh;

	if (!(mesh = (t_mesh *)malloc(sizeof(t_mesh))))
		return (NULL);
	mesh->polygonnum = (size.n.x - 1) * 2 * (size.n.y - 1);
	if (!(mesh->polygons = (t_polygon *)malloc(sizeof(t_polygon)
			* mesh->polygonnum)))
	{
		free(mesh);
		return (NULL);
	}
	mat4_init(&mesh->matrix);
	mesh->sector_id = -1;
	mesh->walls = NULL;
	mesh->nb_walls = 0;
	init_mesh(mesh, size);
	return (mesh);
}
