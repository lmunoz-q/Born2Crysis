/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transbuff_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:52:54 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/09 14:00:54 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	transbuff_push(t_polygon *p)
{
	t_trans_buffer *b;

	if (!(b = get_transbuff()))
		return ;
	if (b->top + 1 < b->size)
	{
		b->top++;
		mf_memcpy(&b->data[b->top], p, sizeof(t_polygon));
	}
}
