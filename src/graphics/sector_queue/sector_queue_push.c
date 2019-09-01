/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_queue_push.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:45:09 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/01 17:42:49 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_sector	*sector_queue_push(t_sector *sector)
{
	static t_stack	*sector_queue = NULL;

	if (!sector_queue)
	{
		sector_queue = stack_create(MAX_PORTALS_PER_SECTOR);
		return (sector_queue_push(sector));
	}
	if (sector == NULL)
		return (stack_pop(sector_queue));
	stack_push(sector_queue, sector);
	if ((int32_t)sector == -1)
		stack_destroy(&sector_queue);
	return (NULL);
}
