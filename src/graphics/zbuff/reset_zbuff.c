/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_zbuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:55:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/21 19:33:18 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	reset_zbuff(double value, size_t size)
{
	size_t		i;
	double	*buff;

	buff = get_zbuff();
	i = -1;
	while (++i < size)
		buff[i] = value;
}
