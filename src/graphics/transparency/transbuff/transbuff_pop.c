/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transbuff_pop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 13:00:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/09 13:06:32 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_polygon	*transbuff_pop(void)
{
	t_trans_buffer	*b;

	if (!(b = get_transbuff()))
		return (NULL);
	return ((b->top > -1) ? &b->data[b->top--] : NULL);
}
