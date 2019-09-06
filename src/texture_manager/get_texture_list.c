/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 21:12:39 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/25 15:21:48 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>
#include "texture_manager.h"

t_texture			*set_texture_list(t_texture *newlist, size_t newsize)
{
	t_world					*world;

	world = get_world();
	if (newlist && newsize)
	{
		world->textures = newlist;
		world->nb_textures = newsize;
	}
	if (newsize == (size_t)-1)
		return ((t_texture *)(size_t)world->nb_textures);
	return (world->textures);
}

size_t				get_texture_list_size(void)
{
	return ((size_t)set_texture_list(NULL, -1));
}

t_texture			*get_texture_list(void)
{
	return (set_texture_list(NULL, 0));
}
