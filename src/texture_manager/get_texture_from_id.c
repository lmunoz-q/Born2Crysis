/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_from_id.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:17:45 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 17:39:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

t_texture	*get_texture_from_id(unsigned int id)
{
	t_texture	*list;
	size_t		size;
	int			i;

	i = -1;
	if (!(list = get_texture_list()))
		return (NULL);
	size = get_texture_list_size();
	while ((size_t)++i < size)
		if (id == list[i].id)
			return (&list[i]);
	puts("Error: Failed to retrieve texture...\n");
	return (NULL);
}
