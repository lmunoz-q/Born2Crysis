/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_polygon_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 22:07:54 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/18 12:40:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_polygon	*get_polygon_buffer(void)
{
	return (set_polygon_buffer(NULL, 0));
}

Uint32		get_polygon_buffer_size()
{
	return((Uint32)set_polygon_buffer(NULL, -2));
}
