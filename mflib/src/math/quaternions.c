/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:11:46 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/06 15:11:46 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mflib.h>

t_vec4d	quat_rotator(t_vec3d axis, double rad)
{
	t_vec4d	out;
	double	t;

	rad /= 2.0;
	out.n.w = cos(rad);
	if ((t = axis.n.x * axis.n.x + axis.n.y * axis.n.y + axis.n.z * axis.n.z)
			!= 1.0)
		t = sin(rad) / sqrt(t);
	else
		t = sin(rad);
	out.n.x = t * axis.n.x;
	out.n.y = t * axis.n.y;
	out.n.z = t * axis.n.z;
	return (out);
}

t_vec4d	quat_multiply(t_vec4d q1, t_vec4d q2)
{
	return ((t_vec4d){{
		q1.n.w * q2.n.x + q2.n.w * q1.n.x + q1.n.y * q2.n.z - q2.n.y * q1.n.z,
		q1.n.w * q2.n.y + q2.n.w * q1.n.y - q1.n.x * q2.n.z + q2.n.x * q1.n.z,
		q1.n.w * q2.n.z + q2.n.w * q1.n.z + q1.n.x * q2.n.y - q2.n.x * q1.n.y,
		q1.n.w * q2.n.w - q1.n.x * q2.n.x - q1.n.y * q2.n.y - q1.n.z * q2.n.z
	}});
}

t_vec4d	quat_inverse(t_vec4d q)
{
	double	t;

	t = -1.0 / (q.n.w * q.n.w + q.n.x * q.n.x + q.n.y * q.n.y + q.n.z * q.n.z);
	return ((t_vec4d){{t * q.n.x, t * q.n.y, t * q.n.z, -t * q.n.w}});
}

t_mat3d	quat_to_mat3d(t_vec4d q)
{
	t_mat3d	out;
	double	t;

	t = vec4_magnitude(q);
	if (t == 0.0)
	{
		mat3_init(&out);
		return (out);
	}
	if (t != 1.0)
		q = vec4scalar_multiply(q, t);
	out.a[0][0] = 1 - 2 * (q.n.y * q.n.y + q.n.z * q.n.z);
	out.a[0][1] = 2 * (q.n.x * q.n.y - q.n.w * q.n.z);
	out.a[0][2] = 2 * (q.n.w * q.n.y + q.n.x * q.n.z);
	out.a[1][0] = 2 * (q.n.w * q.n.z + q.n.x * q.n.y);
	out.a[1][1] = 1 - 2 * (q.n.x * q.n.x + q.n.z * q.n.z);
	out.a[1][2] = 2 * (q.n.y * q.n.z - q.n.w * q.n.x);
	out.a[2][0] = 2 * (q.n.x * q.n.z - q.n.w * q.n.y);
	out.a[2][1] = 2 * (q.n.w * q.n.x + q.n.y * q.n.z);
	out.a[2][2] = 1 - 2 * (q.n.x * q.n.x + q.n.y * q.n.y);
	return (out);
}

t_mat4d	quat_to_mat4d(t_vec4d q)
{
	t_mat4d	out;
	double	t;

	t = vec4_magnitude(q);
	mat4_init(&out);
	if (t == 0.0)
		return (out);
	if (t != 1.0)
		q = vec4scalar_multiply(q, t);
	out.a[0][0] = 1 - 2 * (q.n.y * q.n.y + q.n.z * q.n.z);
	out.a[0][1] = 2 * (q.n.x * q.n.y - q.n.w * q.n.z);
	out.a[0][2] = 2 * (q.n.w * q.n.y + q.n.x * q.n.z);
	out.a[1][0] = 2 * (q.n.w * q.n.z + q.n.x * q.n.y);
	out.a[1][1] = 1 - 2 * (q.n.x * q.n.x + q.n.z * q.n.z);
	out.a[1][2] = 2 * (q.n.y * q.n.z - q.n.w * q.n.x);
	out.a[2][0] = 2 * (q.n.x * q.n.z - q.n.w * q.n.y);
	out.a[2][1] = 2 * (q.n.w * q.n.x + q.n.y * q.n.z);
	out.a[2][2] = 1 - 2 * (q.n.x * q.n.x + q.n.y * q.n.y);
	return (out);
}
