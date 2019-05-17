/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_purger.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:01:46 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/17 19:44:17 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		purge_clipped_polygons(t_polygonlist *l)
{
	t_node *head;

	head = l->list;
	while (head)
	{
		if (((t_polygon *)l->list->data)->is_clipped)
			free(list2_delete(l, head));
		head = head->next;
	}
}
