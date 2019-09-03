/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_perlin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:14:37 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/03 22:31:38 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perlin.h"

static void	gen_points(double *points, int size)
{
	while (--size >= 0)
		points[size] = (double)((mf_rand() % 100000) + 1) / 100000.0;
}

static double	get_perlin_point(double *points, int nb_octaves, double bias, t_vec2i size)
{
	int		i;
	double	noise;
	double	scaleacc;
	double	scale;

	noise = 0;
	i = -1;
	while (++i < nb_octaves)
	{
		int pitch = size.n.x >> i;
	}
}

double		*gen_perlin(t_vec2i	size, int seed, int nb_octaves, double bias)
{
	double		*res;
	double		*points;

	if (!(res = (double *)mf_memalloc(sizeof(double) * size.n.x * size.n.y)))
		return (NULL);
	if (!(points = (double *)mf_memalloc(sizeof(double) * size.n.x * size.n.y)))
	{
		free(res);
		return (NULL);
	}
	mf_seed(seed);
	gen_points(points, (size.n.x * size.n.y));
}