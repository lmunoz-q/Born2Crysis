/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_zbuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:55:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/08 23:29:21 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	reset_zbuff(double value, size_t size)
{
	//size_t		i;
	double	*buff;

	(void)value;
	buff = get_zbuff();
	//i = -1;
	//while (++i < size)
	//		buff[i] = value;
	mf_memset(buff, 0, size * sizeof(double));
}
