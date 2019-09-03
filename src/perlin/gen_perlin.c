/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_perlin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:14:37 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/03 18:43:56 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perlin.h"

double		*gen_perlin(t_vec2i	size, double grid_ratio, int seed)
{
	double		*res;

	if (!(res = (double *)mf_memalloc(sizeof(double) * size.n.x * size.n.y)))
		return (NULL);
	mf_seed(seed);
}