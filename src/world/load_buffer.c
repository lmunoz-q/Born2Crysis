/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:50:38 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 16:47:10 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_polygon		*load_buffer(t_world *world)
{
	t_polygon	*res;
	int			max;
	int			i;
	int			j;

	max = 50;
	i = -1;
	while (++i < world->sectornum)
	{
		j = -1;
		while (++j < world->sectors[i].meshnum)
		{
			if (world->sectors[i].mesh[j].polygonnum > max)
				max = world->sectors[i].mesh[j].polygonnum;
		}
	}
	if (!(res = (t_polygon *)malloc(sizeof(t_polygon) * max * 2)))
		return (NULL);
	set_polygon_buffer(res, max * 2);
	return (res);
}
