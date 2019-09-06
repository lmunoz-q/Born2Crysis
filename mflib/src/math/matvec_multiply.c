/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matvec_multiply.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 23:24:22 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/11 11:55:28 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_vec4d	mat4vec4_multiply(t_mat4d mat, t_vec4d vec)
{
	int		i;
	int		j;
	t_vec4d	tmp;
	double	*xpos;
	double	*ypos;

	i = -1;
	tmp.a[0] = 0;
	tmp.a[1] = 0;
	tmp.a[2] = 0;
	tmp.a[3] = 0;
	ypos = &mat.a[0][0];
	while (++i < 4)
	{
		xpos = vec.a;
		j = -1;
		while (++j < 4)
			tmp.a[i] += (*ypos++) * (*xpos++);
	}
	return (tmp);
}

t_vec3d	mat3vec3_multiply(t_mat3d mat, t_vec3d vec)
{
	int		i;
	int		j;
	t_vec3d	tmp;

	i = -1;
	vec3_clear(&tmp);
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			tmp.a[i] += mat.a[i][j] * vec.a[j];
		}
	}
	return (tmp);
}

t_vec2d	mat2vec2_multiply(t_mat2d mat, t_vec2d vec)
{
	int		i;
	int		j;
	t_vec2d	tmp;

	i = -1;
	vec2_clear(&tmp);
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
		{
			tmp.a[i] += mat.a[i][j] * vec.a[j];
		}
	}
	return (tmp);
}
