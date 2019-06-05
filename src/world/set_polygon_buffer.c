/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_polygon_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 22:05:25 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/05 22:57:59 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_polygon		*set_polygon_buffer(t_polygon *addr)
{
	static t_polygon *buffer = NULL;

	if (addr)
		buffer = addr;
	return (buffer);
}