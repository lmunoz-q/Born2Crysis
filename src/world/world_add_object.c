/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_add_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 17:05:14 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/19 00:16:33 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void		world_add_object(t_object *object, t_world *world, int sector_id)
{
	t_sector		*sector;
	t_object		*obj_tmp;

	if (!(sector = get_sector(sector_id, world)))
		return ;
	if (sector->objects == NULL)
		sector->objectnum = 0;
	if (!(obj_tmp = (t_object *)malloc(sizeof(t_object) * (sector->objectnum + 1))))
		return ;
	mf_memcpy(obj_tmp, sector->objects, sizeof(t_object) * sector->objectnum);
	mf_memcpy(&obj_tmp[sector->objectnum], object, sizeof(t_object));
	if (sector->objects)
		free(sector->objects);
	sector->objectnum++;
	sector->objects = obj_tmp;
}