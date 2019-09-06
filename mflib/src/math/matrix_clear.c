/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 23:30:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/13 14:51:42 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

void			mat4_clear(t_mat4d *mat)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			mat->a[i][j] = 0;
	}
}

void			mat3_clear(t_mat3d *mat)
{
	int i;
	int j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			mat->a[i][j] = 0;
	}
}

void			mat2_clear(t_mat2d *mat)
{
	mat->a[0][0] = 0;
	mat->a[0][1] = 0;
	mat->a[1][0] = 0;
	mat->a[1][1] = 0;
}
