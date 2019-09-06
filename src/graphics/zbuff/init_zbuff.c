/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_zbuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:57:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/30 14:00:14 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

double				*init_zbuff(int32_t size)
{
	static double	*zbuff = NULL;

	if (!zbuff && size != -1)
		zbuff = (double *)malloc(sizeof(double) * size);
	return (zbuff);
}
