/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_increase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 16:54:59 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 17:08:32 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_bool    buffer_increase(size_t size)
{
    t_polygon *buff;
    t_polygon *tmp;

    printf("buffer increased from %d to %zu\n", get_polygon_buffer_size(), size);
    buff = get_polygon_buffer();
    if (!(tmp = (t_polygon *)malloc(sizeof(t_polygon) * size * 2)))
        return (FALSE);
    set_polygon_buffer(tmp, size);
    free(buff);
    
    return (TRUE);
}