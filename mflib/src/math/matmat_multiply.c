/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matmat_multiply.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 23:28:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/13 14:51:35 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_mat4d	mat4mat4_multiply(t_mat4d mat1, t_mat4d mat2)
{
	int		i;
	int		j;
	int		k;
	t_mat4d	out;

	i = -1;
	mat4_clear(&out);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			while (++k < 4)
				out.a[i][j] += mat1.a[i][k] * mat2.a[k][j];
		}
	}
	return (out);
}

t_mat3d	mat3mat3_multiply(t_mat3d mat1, t_mat3d mat2)
{
	int		i;
	int		j;
	int		k;
	t_mat3d	out;

	i = -1;
	mat3_clear(&out);
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			k = -1;
			while (++k < 3)
				out.a[i][j] += mat1.a[i][k] * mat2.a[k][j];
		}
	}
	return (out);
}

t_mat2d	mat2mat2_multiply(t_mat2d mat1, t_mat2d mat2)
{
	int		i;
	int		j;
	int		k;
	t_mat2d	out;

	i = -1;
	mat2_clear(&out);
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
		{
			k = -1;
			while (++k < 2)
				out.a[i][j] += mat1.a[i][k] * mat2.a[k][j];
		}
	}
	return (out);
}
