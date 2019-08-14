/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_world.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:18:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/03 16:21:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_world		*set_world(t_world *world)
{
	static t_world	*world_s = NULL;

	if (world)
		world_s = world;
	return (world_s);
}

t_world		*get_world(void)
{
	return (set_world(NULL));
}
