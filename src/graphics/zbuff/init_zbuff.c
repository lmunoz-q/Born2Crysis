/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_zbuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:57:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 16:51:18 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

double				*init_zbuff(size_t size)
{
	static double	*zbuff = NULL;

	if (size != (size_t)-1)
		zbuff = (double *)malloc(sizeof(double) * size);
	return (zbuff);
}
