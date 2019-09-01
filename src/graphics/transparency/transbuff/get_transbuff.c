/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_transbuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:47:29 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/01 17:46:10 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_trans_buffer	*get_transbuff(void)
{
	static t_trans_buffer	transbuff;

	if (!transbuff.data)
	{
		transbuff.data = (t_polygon *)malloc(sizeof(t_polygon)
			* TRANS_BUFF_SIZE);
		transbuff.top = -1;
		transbuff.size = TRANS_BUFF_SIZE;
	}
	return (&transbuff);
}
