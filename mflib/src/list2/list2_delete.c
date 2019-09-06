/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:32:46 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/17 19:36:34 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist2.h"

void	*list2_delete(t_list2 *list, t_node *node)
{
	void *tmp;

	if (!node)
		return (NULL);
	tmp = node->data;
	if (node->next)
		node->next->prev = node->prev;
	if (node->prev)
		node->prev->next = node->next;
	else
		list->list = node->next;
	free(node);
	list->size--;
	return (tmp);
}
