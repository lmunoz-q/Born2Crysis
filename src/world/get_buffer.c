/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_buffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:50:38 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/04 23:02:11 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_polygon	*get_buffer(t_world *world)
{
	int max;
	int i;
	int j;

	max = 10;
	i = -1;
	while (++i < world->sectornum)
	{
		j = -1;
		if (world->sectors[i].polygonnum > max)
			max = world->sectors[i].polygonnum;
		while (++j < world->sectors[i].objectnum)
		{
			if (world->sectors[i].objects[j].polygonnum > max)
				max = world->sectors[i].objects[j].polygonnum;
		}
	}
	return ((t_polygon *)malloc(sizeof(t_polygon) * max));
}