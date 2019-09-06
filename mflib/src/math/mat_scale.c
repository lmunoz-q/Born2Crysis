/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 22:33:25 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/27 15:25:46 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_mat4d		mat4_scale(t_mat4d mat, double x, double y, double z)
{
	t_mat4d tmp;

	mat4_init(&tmp);
	mat.a[0][0] *= x;
	mat.a[1][1] *= y;
	mat.a[2][2] *= z;
	return (mat4mat4_multiply(tmp, mat));
}

t_mat3d		mat3_scale(t_mat3d mat, double x, double y)
{
	t_mat3d tmp;

	mat3_init(&tmp);
	mat.a[0][0] *= x;
	mat.a[1][1] *= y;
	return (mat3mat3_multiply(tmp, mat));
}
