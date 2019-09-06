/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 19:26:44 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/17 19:30:34 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist2.h"

void	list2_insert(t_list2 *list, t_node *node, void *data)
{
	t_node *new;

	if (!node)
	{
		list2_push(list, data);
		return ;
	}
	if (!(new = (t_node *)malloc(sizeof(t_node))))
		return ;
	new->data = data;
	new->prev = node;
	new->next = node->next;
	if (new->next)
		new->next->prev = new;
	node->next = new;
	list->size++;
}
