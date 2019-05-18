/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_purger.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:01:46 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/18 13:10:46 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		purge_clipped_polygons(t_polygonlist *l)
{
	t_node *head;
	t_node *tmp;

	head = l->list;
	while (head)
	{
		tmp = head->next;
		if (((t_polygon *)head->data)->is_clipped)
			free(list2_delete(l, head));
		head = tmp;
	}
}
