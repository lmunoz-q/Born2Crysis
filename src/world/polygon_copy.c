/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:35:46 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/17 18:37:59 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_polygon	*polygon_copy(t_polygon *p)
{
	t_polygon *new;

	if (!(new = (t_polygon *)malloc(sizeof(t_polygon))))
		return (NULL);
	mf_memcpy(new, p, sizeof(t_polygon));
	return (new);
}
