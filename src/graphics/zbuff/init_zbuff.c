/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_zbuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:57:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/09 01:23:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

double *init_zbuff(size_t size)
{
	static double	*zbuff = NULL;

	if (!zbuff)
		zbuff = (double *)malloc(sizeof(double) * size);
	return (zbuff);
}