/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 23:54:27 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 19:48:40 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_sector	*get_sector(int32_t id, t_world *world)
{
	int32_t	i;

	i = -1;
	while (++i < world->sectornum)
		if (world->sectors[i].id == id)
			return (&world->sectors[i]);
	return (NULL);
}
