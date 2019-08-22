/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 21:12:39 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 17:40:24 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

t_texture			*set_texture_list(t_texture *newlist, size_t newsize)
{
	static t_texture	*list = NULL;
	static size_t		size = 0;

	if (newlist && newsize)
	{
		list = newlist;
		size = newsize;
	}
	if (newsize == (size_t)-1)
		return ((t_texture *)size);
	return (list);
}

size_t				get_texture_list_size(void)
{
	return ((size_t)set_texture_list(NULL, -1));
}

t_texture			*get_texture_list(void)
{
	return (set_texture_list(NULL, 0));
}
