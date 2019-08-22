/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygons_set_trans.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:07:11 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/21 23:11:21 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		polygons_set_trans(t_polygon *p, int size, int transparency)
{
	int i;

	i = -1;
	while (++i < size)
	{
		p[i].transparency = transparency;
	}
}