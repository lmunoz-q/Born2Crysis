/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_increase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 16:54:59 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 21:43:05 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_bool	buffer_increase(size_t size)
{
	t_polygon *buff;
	t_polygon *tmp;

	buff = get_polygon_buffer();
	if (buff)
		free(buff);
	if (!(tmp = (t_polygon *)malloc(sizeof(t_polygon) * size * 2)))
		return (FALSE);
	mf_memset(tmp, 0, sizeof(t_polygon) * size * 2);
	set_polygon_buffer(tmp, size);
	return (TRUE);
}
