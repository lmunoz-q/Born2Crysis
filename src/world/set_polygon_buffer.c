/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_polygon_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 22:05:25 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/18 12:41:03 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_polygon		*set_polygon_buffer(t_polygon *addr, int size)
{
	static t_polygon	*buffer = NULL;
	static long int		buffer_size = 0;

	if (addr)
	{
		buffer = addr;
		buffer_size = size;
	}
	if (size == -2)
		return ((t_polygon *)buffer_size);
	return (buffer);
}