/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_from_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:18:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/25 15:06:29 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <physic.h>



/*
** 		t = vec3_dot(tmp, tmp); square of magnitude
** 		t_wall	wall_from_triangle(t_vec3d triangle[3]) clock-wise notation
*/

static inline t_wall	i_finishing_touch(t_wall out, t_vec3d triangle[3])
{
	double	t;
	double	msd;
	int		i;
	t_vec3d	tmp;

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

t_wall					wall_from_triangle(t_vec3d triangle[3], t_mat4d mat)
{
	t_wall	out;

	out.vertices[0] = triangle[0]; //TODO: NE PAS RETIRER CE COMMENTAIRE!!!!!!
	out.vertices[1] = triangle[1]; //TODO: changer l'application de la matrice
	out.vertices[2] = triangle[2]; //TODO: sur les vertices @Hugo @Marek
	triangle[0] = mat4vec4_multiply(mat,
		(t_vec4d){.c3 = {triangle[0], 1}}).c3.vec3d;
	triangle[1] = mat4vec4_multiply(mat,
		(t_vec4d){.c3 = {triangle[1], 1}}).c3.vec3d;
	triangle[2] = mat4vec4_multiply(mat,
		(t_vec4d){.c3 = {triangle[2], 1}}).c3.vec3d;
	out.normal = vec3_normalize(vec3vec3_crossproduct(
		vec3vec3_substract(triangle[1], triangle[0]),
		vec3vec3_substract(triangle[2], triangle[0])));
	out.center = vec3scalar_multiply(vec3vec3_add(
		vec3vec3_add(triangle[0], triangle[1]), triangle[2]), 1.0 / 3.0);
	return (i_finishing_touch(out, triangle));
}
