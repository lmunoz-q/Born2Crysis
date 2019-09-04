/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:12:34 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 20:32:22 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERLIN_H
# define PERLIN_H

# include "mflib.h"

typedef struct	s_perlin
{
	double		*noise;
	double		*res;
	double		octaves;
	double		bias;
	double		scale;
	double		scale_sum;
	t_vec2i		size;
	t_vec2i		delta_one;
	t_vec2i		delta_two;
	t_vec2d		ratios;
	t_vec2d		avg_x;
}				t_perlin;

double			*gen_perlin(t_vec2i	size, int seed, int nb_octaves, double bias);

#endif
