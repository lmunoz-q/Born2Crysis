/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:55:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/18 21:10:05 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	j_calculate(t_polygon *p, t_light_comp *lcomp, t_2v3d2i a)
{
	p[a.i].v_light.a[0] += (lcomp->lights[a.j].intensity
		/ (vec3_magnitude(a.tmp) * lcomp->lights[a.j].fallof))
			* ((vec3_dot(lcomp->lights[a.j].dir, p[a.i].normal) - 1.0)
			/ -2.0) * vec3_dot(a.tmp_n, p[a.i].normal);
	p[a.i].v_light.a[0] = mf_clamp_double(p[a.i].v_light.a[0], 0, 0.99);
	a.tmp = vec3vec3_substract(p[a.i].v12.c3.vec3d,
		lcomp->lights[a.j].pos.c3.vec3d);
	a.tmp_n = vec3_normalize(a.tmp);
	p[a.i].v_light.a[1] += (lcomp->lights[a.j].intensity
		/ (vec3_magnitude(a.tmp) * lcomp->lights[a.j].fallof))
			* ((vec3_dot(lcomp->lights[a.j].dir, p[a.i].normal) - 1.0) / -2.0)
			* vec3_dot(a.tmp_n, p[a.i].normal);
	p[a.i].v_light.a[1] = mf_clamp_double(p[a.i].v_light.a[1], 0, 0.99);
	a.tmp = vec3vec3_substract(p[a.i].v20.c3.vec3d,
		lcomp->lights[a.j].pos.c3.vec3d);
	a.tmp_n = vec3_normalize(a.tmp);
	p[a.i].v_light.a[2] += (lcomp->lights[a.j].intensity
		/ (vec3_magnitude(a.tmp) * lcomp->lights[a.j].fallof))
			* ((vec3_dot(lcomp->lights[a.j].dir, p[a.i].normal) - 1.0) / -2.0)
			* vec3_dot(a.tmp_n, p[a.i].normal);
	p[a.i].v_light.a[2] = mf_clamp_double(p[a.i].v_light.a[2], 0, 0.99);
}

void	i_calculate(t_polygon *p, t_light_comp *lcomp, t_2v3d2i a)
{
	a.tmp = vec3vec3_substract(p[a.i].v01.c3.vec3d,
		lcomp->lights[a.j].pos.c3.vec3d);
	a.tmp_n = vec3_normalize(a.tmp);
	p[a.i].v_light.a[0] += (lcomp->lights[a.j].intensity
		/ (vec3_magnitude(a.tmp) * lcomp->lights[a.j].fallof))
			* (vec3_dot(a.tmp_n, p[a.i].normal) + 1.0) / 2.0;
	p[a.i].v_light.a[0] = mf_clamp_double(p[a.i].v_light.a[0], 0, 0.99);
	a.tmp = vec3vec3_substract(p[a.i].v12.c3.vec3d,
		lcomp->lights[a.j].pos.c3.vec3d);
	a.tmp_n = vec3_normalize(a.tmp);
	p[a.i].v_light.a[1] += (lcomp->lights[a.j].intensity
		/ (vec3_magnitude(a.tmp) * lcomp->lights[a.j].fallof))
			* (vec3_dot(a.tmp_n, p[a.i].normal) + 1.0) / 2.0;
	p[a.i].v_light.a[1] = mf_clamp_double(p[a.i].v_light.a[1], 0, 0.99);
	a.tmp = vec3vec3_substract(p[a.i].v20.c3.vec3d,
		lcomp->lights[a.j].pos.c3.vec3d);
	a.tmp_n = vec3_normalize(a.tmp);
	p[a.i].v_light.a[2] += (lcomp->lights[a.j].intensity
		/ (vec3_magnitude(a.tmp) * lcomp->lights[a.j].fallof))
			* (vec3_dot(a.tmp_n, p[a.i].normal) + 1.0) / 2.0;
	p[a.i].v_light.a[2] = mf_clamp_double(p[a.i].v_light.a[2], 0, 0.99);
}

void	calculate_lighting(t_polygon *p, int count, t_light_comp *lcomp)
{
	t_2v3d2i	a;

	a.i = -1;
	while (++a.i < count)
	{
		a.j = -1;
		while (lcomp && ++a.j < (int)lcomp->light_count)
		{
			a.tmp = vec3vec3_substract(p[a.i].v01.c3.vec3d,
				lcomp->lights[a.j].pos.c3.vec3d);
			a.tmp_n = vec3_normalize(a.tmp);
			if (lcomp->lights[a.j].type == POINT_LIGHT)
				i_calculate(p, lcomp, a);
			if (lcomp->lights[a.j].type == DIRECTIONAL_LIGHT)
				j_calculate(p, lcomp, a);
		}
		if (!lcomp || lcomp->light_count == 0)
			p[a.i].v_light = (t_vec3d){.a = {0.99, 0.99, 0.99}};
	}
}
