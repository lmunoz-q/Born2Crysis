/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_purger.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:01:46 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/09 18:05:04 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		purge_clipped_polygons(t_polygonlist *l)
{
	while (l->list && ((t_polygon *)l->list->data)->is_clipped)
		list2_pop(l);
}
