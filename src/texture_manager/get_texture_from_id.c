/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_from_id.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:17:45 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/10 19:55:30 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

t_texture	get_texture_from_id(unsigned int id)
{
	t_node	*head;
	t_list2	*l;

	if (!(l = get_texture_list()))
		return (NULL);
	head = l->list;
	while (head)
		if (id == ((t_texture)head->data)->id)
			return (head->data);
		else
			head = head->next;
	puts("Error: Failed to retrieve texture...\n");
	return (NULL);
}