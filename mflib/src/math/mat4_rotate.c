/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 23:03:42 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/27 14:30:33 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_mat4d	mat4_rotate_yaw(t_mat4d mat, double angle)
{
	t_mat4d		tmp;
	double		new_angle;

	new_angle = angle * 3.14159265359 / 180.0;
	mat4_init(&tmp);
	tmp.a[1][1] = cos(new_angle);
	tmp.a[1][2] = -sin(new_angle);
	tmp.a[2][1] = sin(new_angle);
	tmp.a[2][2] = cos(new_angle);
	return (mat4mat4_multiply(tmp, mat));
}

t_mat4d	mat4_rotate_pitch(t_mat4d mat, double angle)
{
	t_mat4d		tmp;
	double		new_angle;

	new_angle = angle * 3.14159265359 / 180.0;
	mat4_init(&tmp);
	tmp.a[0][0] = cos(new_angle);
	tmp.a[2][0] = -sin(new_angle);
	tmp.a[0][2] = sin(new_angle);
	tmp.a[2][2] = cos(new_angle);
	return (mat4mat4_multiply(tmp, mat));
}

t_mat4d	mat4_rotate_roll(t_mat4d mat, double angle)
{
	t_mat4d		tmp;
	double		new_angle;

	new_angle = angle * 3.14159265359 / 180.0;
	mat4_init(&tmp);
	tmp.a[0][0] = cos(new_angle);
	tmp.a[0][1] = -sin(new_angle);
	tmp.a[1][0] = sin(new_angle);
	tmp.a[1][1] = cos(new_angle);
	return (mat4mat4_multiply(tmp, mat));
}

t_mat3d	mat3_rotate(t_mat3d mat, double angle)
{
	t_mat3d		tmp;
	double		new_angle;

	new_angle = angle * 3.14159265359 / 180.0;
	mat3_init(&tmp);
	tmp.a[0][0] = cos(new_angle);
	tmp.a[0][1] = -sin(new_angle);
	tmp.a[1][0] = sin(new_angle);
	tmp.a[1][1] = cos(new_angle);
	return (mat3mat3_multiply(tmp, mat));
}
