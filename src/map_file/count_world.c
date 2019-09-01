/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 22:44:32 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/31 22:44:39 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map_file.h>

t_counter	count_world(t_world *w)
{
	t_counter	out;
	int32_t		i;
	int32_t		j;

	out = (t_counter){w->sectornum, 0, 0, 0, 0, 0, w->nb_textures, 0};
	i = -1;
	while (++i < w->sectornum)
	{
		out.nb_mesh += w->sectors[i].meshnum;
		out.nb_lights += w->sectors[i].lights.light_count;
		out.nb_entities += w->sectors[i].nb_entities;
		j = -1;
		while (++j < w->sectors[i].meshnum)
		{
			out.nb_polygons += w->sectors[i].mesh[j].polygonnum;
			out.nb_walls += w->sectors[i].mesh[j].nb_walls;
		}
	}
	i = -1;
	while (++i < w->nb_textures)
		out.nb_pixels += w->textures[i].size.n.x * w->textures[i].size.n.y;
	return (out);
}
