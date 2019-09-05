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

	out = (t_counter){w->sectornum, 0, 0, 0, 0, w->nb_textures, 0,
					w->lib.nb_functions, 0, 0, 0};
	i = -1;
	while (++i < w->sectornum)
	{
		out.nb_mesh += w->sectors[i].meshnum;
		out.nb_lights += w->sectors[i].lights.light_count;
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
	i = -1;
	while (++i < (int32_t)w->lib.nb_functions)
	{
		out.nb_code += w->lib.function[i].code_size;
		out.nb_alias += w->lib.function[i].alias_size;
		out.nb_symbols += w->lib.function[i].needed_symbols;
	}
	return (out);
}
