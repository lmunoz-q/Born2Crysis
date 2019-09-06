/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 22:41:27 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/13 14:51:47 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

void			mat4_init(t_mat4d *mat)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			mat->a[i][j] = (i == j) ? 1 : 0;
	}
}

void			mat3_init(t_mat3d *mat)
{
	int i;
	int j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			mat->a[i][j] = (i == j) ? 1 : 0;
	}
}

void			mat2_init(t_mat2d *mat)
{
	mat->a[0][0] = 1;
	mat->a[0][1] = 0;
	mat->a[1][0] = 0;
	mat->a[1][1] = 1;
}
