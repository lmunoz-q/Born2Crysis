/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_perlin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:14:37 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 02:12:50 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perlin.h"

static void	gen_points(double *points, int size)
{
	while (--size >= 0)
		points[size] = (double)((mf_rand() % 100000) + 1) / 100000.0;
}

static void	calc_avg_x(t_perlin *perlin, int pitch, int x, int y)
{
	perlin->delta_two = (t_vec2i){
		.a = {(perlin->delta_one.n.x + pitch) % perlin->size.n.x,
			(perlin->delta_one.n.y + pitch) % perlin->size.n.x}};
			perlin->ratios = (t_vec2d){
		.a = {(double)(x - perlin->delta_one.n.x) / (double)pitch,
				(double)(y - perlin->delta_one.n.y) / (double)pitch}};
	perlin->avg_x = (t_vec2d){.a = {(1.0 - perlin->ratios.n.x)
		* perlin->noise[perlin->delta_one.n.y * perlin->size.n.x
		+ perlin->delta_one.n.x] + perlin->ratios.n.x
		* perlin->noise[perlin->delta_one.n.y * perlin->size.n.x
		+ perlin->delta_two.n.x], (1.0 - perlin->ratios.n.x)
		* perlin->noise[perlin->delta_two.n.y * perlin->size.n.x
		+ perlin->delta_one.n.x] + perlin->ratios.n.x
		* perlin->noise[perlin->delta_two.n.y * perlin->size.n.x
		+ perlin->delta_two.n.x]}};
}

static double	get_perlin_point(t_perlin *perlin, int x, int y)
{
	int		i;
	int		pitch;
	double	res;

	res = 0;
	i = 0;
	perlin->scale = 1.0;
	perlin->scale_sum = 0;
	while (++i < perlin->octaves)
	{
		pitch = perlin->size.n.x >> i;
		if (pitch < 1)
			break ;
		perlin->delta_one = (t_vec2i){.a = {(x / pitch) * pitch,
											(y / pitch) * pitch}};
		calc_avg_x(perlin, pitch, x, y);
		perlin->scale_sum += perlin->scale;
		res += (perlin->ratios.n.y * (perlin->avg_x.n.y - perlin->avg_x.n.x)
			+ perlin->avg_x.n.x) * perlin->scale;
		perlin->scale = perlin->scale / perlin->bias;
	}
	return (res / perlin->scale_sum);
}

static void	fill_noise(t_perlin *perlin)
{
	int i;
	int j;

	i = -1;
	while (++i < perlin->size.n.y)
	{
		j = -1;
		while (++j < perlin->size.n.x)
		{
			perlin->res[i * perlin->size.n.x + j] = get_perlin_point(perlin, j, i);
		}
	}
}

double		*gen_perlin(t_vec2i	size, int seed, int nb_octaves, double bias)
{
	t_perlin	perlin;

	perlin = (t_perlin){.bias = bias, .octaves = nb_octaves,
						.size = size};
	if (!(perlin.res = (double *)mf_memalloc(sizeof(double) * size.n.x * size.n.y)))
		return (NULL);
	if (!(perlin.noise = (double *)mf_memalloc(sizeof(double) * size.n.x * size.n.y)))
	{
		free(perlin.res);
		return (NULL);
	}
	mf_seed(seed);
	gen_points(perlin.noise, (size.n.x * size.n.y));
	fill_noise(&perlin);
	return (perlin.res);
}