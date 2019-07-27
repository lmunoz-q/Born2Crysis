/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_at.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:20:26 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/17 22:58:23 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static void	quick_inverse(t_mat4d *mat)
{
	t_mat4d	tmp;
	int		i;

	i = -1;
	while (++i < 3)
	{
		tmp.a[i][0] = mat->a[0][i];
		tmp.a[i][1] = mat->a[1][i];
		tmp.a[i][2] = mat->a[2][i];
		tmp.a[i][3] = mat->a[0][3] * tmp.a[i][0] + mat->a[1][3] * tmp.a[i][1]
			+ mat->a[2][3] * tmp.a[i][2];
	}
	
	tmp.a[3][0] = 0.0;
	tmp.a[3][1] = 0.0;
	tmp.a[3][2] = 0.0;
	tmp.a[3][3] = 1.0;
	*mat = tmp;
}

t_mat4d	look_at(t_vec3d from, t_vec3d to, t_vec3d tmp_up)
{
	t_vec3d	forward;
	t_vec3d	right;
	t_vec3d	up;
	int		i;
	t_mat4d	out;

	forward = vec3_normalize(vec3vec3_substract(from, to));
	right = vec3_normalize(vec3vec3_crossproduct(tmp_up, forward));
	up = vec3vec3_crossproduct(forward, right);
	mat4_init(&out);
	i = -1;
	while (++i < 3)
	{
		out.a[i][0] = right.a[i];
		out.a[i][1] = up.a[i];
		out.a[i][2] = forward.a[i];
		out.a[i][3] = -from.a[i];
	}
	quick_inverse(&out);
	return (out);
}
