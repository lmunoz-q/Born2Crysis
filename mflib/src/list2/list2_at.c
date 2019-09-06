/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 21:05:07 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/19 21:09:38 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist2.h"

void				*list2_at(t_list2 *list, int index)
{
	t_node	*head;
	int		i;

	i = -1;
	head = list->list;
	if (list->size == 0)
		return (NULL);
	while (head->next && ++i < index)
		head = head->next;
	return (head->data);
}
