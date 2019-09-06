/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:26:17 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/17 19:38:41 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist2.h"

int				list2_push(t_list2 *list, void *data)
{
	t_node *new;
	t_node *tmp;

	if (!(new = (t_node *)malloc(sizeof(t_node))))
		return (0);
	tmp = list->list;
	list->list = new;
	new->next = tmp;
	new->prev = NULL;
	new->data = data;
	list->size++;
	return (1);
}
