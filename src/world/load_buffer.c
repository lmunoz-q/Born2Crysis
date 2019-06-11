/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:50:38 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/11 21:24:32 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

int total = 0;

static int	check_object(int max, t_object *obj)
{
	int i;

	i = -1;
	while (++i < obj->sub_object_num)
		max = check_object(max, &obj->sub_object[i]);
	i = -1;
	while (++i < obj->meshnum)
	{
		total += obj->mesh[i].polygonnum;
		max = (max < obj->mesh[i].polygonnum) ? obj->mesh[i].polygonnum : max;
	}
	return (max);
}

t_polygon	*load_buffer(t_world *world)
{
	t_polygon *res;
	int max;
	int i;
	int j;

	max = 50;
	i = -1;
	while (++i < world->sectornum)
	{
		j = -1;
		while (++j < world->sectors[i].meshnum)
		{
			total += world->sectors[i].mesh[j].polygonnum;
			if (world->sectors[i].mesh[j].polygonnum > max)
				max = world->sectors[i].mesh[j].polygonnum;
		}
		j = -1;
		while (++j < world->sectors[i].objectnum)
			max = check_object(max, &world->sectors[i].objects[j]);
	}
	printf("Total polygons is %d!\n", total);
	if (!(res = (t_polygon *)malloc(sizeof(t_polygon) * max * 2)))
		return (NULL);
	return (res);
}
