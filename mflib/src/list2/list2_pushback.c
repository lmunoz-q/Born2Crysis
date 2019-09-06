/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_pushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:31:18 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/17 19:39:00 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist2.h"

int				list2_pushback(t_list2 *list, void *data)
{
	t_node	*new;
	t_node	*head;

	if (!(new = (t_node *)malloc(sizeof(t_node))))
		return (0);
	head = list->list;
	while (head && head->next)
		head = head->next;
	new->prev = head;
	new->next = NULL;
	new->data = data;
	if (head)
		head->next = new;
	else
		list->list = new;
	list->size++;
	return (1);
}
