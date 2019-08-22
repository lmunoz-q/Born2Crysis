/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 23:54:27 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/05 22:58:37 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_sector	*get_sector(Uint32 id, t_world *world)
{
	Uint32	i;

	i = (Uint32)-1;
	while (++i < world->sectornum)
		if (world->sectors[i].id == id)
			return (&world->sectors[i]);
	return (NULL);
}
