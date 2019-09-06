/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_toarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 00:52:35 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/25 00:57:58 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist2.h"

void				**list2_toarray(t_list2 *list, int *list_size)
{
	void	**tab;
	int		i;
	t_node	*head;

	if (!(tab = (void **)malloc(sizeof(void *) * list->size)))
		return (NULL);
	*list_size = list->size;
	head = list->list;
	i = 0;
	while (head)
	{
		tab[i++] = head->data;
		head = head->next;
	}
	return (tab);
}
