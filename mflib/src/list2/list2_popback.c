/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_popback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 20:47:04 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/26 17:15:33 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist2.h"

void				*list2_popback(t_list2 *list)
{
	t_node	*head;
	t_node	*tmp;
	void	*data;

	if (list->size == 0 || !list->list)
		return (NULL);
	list->size--;
	head = list->list;
	while (head->next)
		head = head->next;
	data = head->data;
	tmp = head->prev;
	if (list->size == 1)
		list->list = NULL;
	if (list->size > 1)
		tmp->next = NULL;
	free(head);
	return (data);
}
