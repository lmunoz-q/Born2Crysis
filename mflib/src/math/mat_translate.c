/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 22:26:49 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/13 14:51:23 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_mat4d	mat4_translate(t_mat4d mat, double x, double y, double z)
{
	t_mat4d tmp;

	mat4_init(&tmp);
	tmp.a[0][3] += x;
	tmp.a[1][3] += y;
	tmp.a[2][3] += z;
	return (mat4mat4_multiply(tmp, mat));
}

t_mat3d	mat3_translate(t_mat3d mat, double x, double y)
{
	t_mat3d tmp;

	mat3_init(&tmp);
	tmp.a[0][2] += x;
	tmp.a[1][2] += y;
	return (mat3mat3_multiply(tmp, mat));
}
