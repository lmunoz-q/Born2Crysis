/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_queue_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:45:09 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/03 14:53:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_sector	*sector_queue_push(t_sector *sector)
{
	static t_list2	*sector_queue = NULL;

	if (!sector_queue)
	{
		sector_queue = list2_create();
		return (sector_queue_push(sector));
	}
	if (sector == NULL)
		return (list2_pop(sector_queue));
	list2_push(sector_queue, sector);
	return (NULL);
}
