/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_trans_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:14:13 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/08 13:24:57 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_stack		*get_trans_buffer()
{
	static t_stack	*tbuff = NULL;

	if (!tbuff)
		tbuff = stack_create(TRANS_BUFF_SIZE);
	return (tbuff);
}