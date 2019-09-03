/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_perlin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:14:37 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/03 18:54:41 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perlin.h"

static void	gen_points(double *points, int size)
{
	
}

double		*gen_perlin(t_vec2i	size, int chunk_size, int seed)
{
	double		*res;
	double		*points;

	if (!(res = (double *)mf_memalloc(sizeof(double) * size.n.x * size.n.y)))
		return (NULL);
	if (!(points = (double *)mf_memalloc(sizeof(double)
		* ((size.n.x * size.n.y) / chunk_size))))
	{
		free(res);
		return (NULL);
	}
	mf_seed(seed);
	gen_points(points, (size.n.x * size.n.y) / chunk_size);

}