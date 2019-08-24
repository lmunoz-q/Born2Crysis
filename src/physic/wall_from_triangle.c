/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_from_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:18:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/24 10:45:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <physic.h>

/*
** 		t = vec3_dot(tmp, tmp); square of magnitude
** 		t_wall	wall_from_triangle(t_vec3d triangle[3]) clock-wise notation
*/

t_wall		wall_from_triangle(t_vec3d triangle[3])
{
	t_wall	out;
	double	t;
	double	msd;
	int		i;
	t_vec3d	tmp;

	out.vertices[0] = triangle[0];
	out.vertices[1] = triangle[1];
	out.vertices[2] = triangle[2];
	out.normal = vec3_normalize(vec3vec3_crossproduct(
		vec3vec3_substract(triangle[1], triangle[0]),
		vec3vec3_substract(triangle[2], triangle[0])));
	out.center = vec3scalar_multiply(vec3vec3_add(
		vec3vec3_add(triangle[0], triangle[1]), triangle[2]), 1.0 / 3.0);
	msd = 0.0;
	i = -1;
	while (++i < 3)
	{
		tmp = vec3vec3_substract(triangle[i], out.center);
		t = vec3_dot(tmp, tmp);
		if (t > msd)
			msd = t;
	}
	out.radius = sqrt(msd) * 2.0;
	out.friction = 1.0;
	out.on_contact_trigger = 0;
	return (out);
}
