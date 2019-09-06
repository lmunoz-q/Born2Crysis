/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:39:12 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/26 17:12:14 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist2.h"

void				*list2_pop(t_list2 *list)
{
	t_node	*tmp;
	void	*data;

	if (!list->list || list->size == 0)
		return (NULL);
	list->size--;
	tmp = list->list;
	list->list = list->list->next;
	if (list->list)
		list->list->prev = NULL;
	data = tmp->data;
	free(tmp);
	return (data);
}
