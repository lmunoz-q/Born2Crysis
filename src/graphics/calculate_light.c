/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:55:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/27 13:34:38 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	j_calculate(t_polygon *p, int i, int j, t_light_comp *lcomp, t_2vec3d a)
{
	p[i].v_light.a[0] += (lcomp->lights[j].intensity / (vec3_magnitude(a.tmp)
		* lcomp->lights[j].fallof)) * ((vec3_dot(lcomp->lights[j].dir,
			p[i].normal) - 1.0) / -2.0) * vec3_dot(a.tmp_n, p[i].normal);
	p[i].v_light.a[0] = mf_clamp_double(p[i].v_light.a[0], 0, 1.0);
	a.tmp = vec3vec3_substract(p[i].v12.c3.vec3d, lcomp->lights[j].pos.c3.vec3d);
	a.tmp_n = vec3_normalize(a.tmp);
	p[i].v_light.a[1] += (lcomp->lights[j].intensity / (vec3_magnitude(a.tmp)
		* lcomp->lights[j].fallof)) * ((vec3_dot(lcomp->lights[j].dir,
			p[i].normal) - 1.0) / -2.0) * vec3_dot(a.tmp_n, p[i].normal);
	p[i].v_light.a[1] = mf_clamp_double(p[i].v_light.a[1], 0, 1.0);
	a.tmp = vec3vec3_substract(p[i].v20.c3.vec3d, lcomp->lights[j].pos.c3.vec3d);
	a.tmp_n = vec3_normalize(a.tmp);
	p[i].v_light.a[2] += (lcomp->lights[j].intensity / (vec3_magnitude(a.tmp)
		* lcomp->lights[j].fallof)) * ((vec3_dot(lcomp->lights[j].dir,
			p[i].normal) - 1.0) / -2.0) * vec3_dot(a.tmp_n, p[i].normal);
	p[i].v_light.a[2] = mf_clamp_double(p[i].v_light.a[2], 0, 1.0);
}

void	i_calculate(t_polygon *p, int i, int j, t_light_comp *lcomp, t_2vec3d a)
{
	a.tmp = vec3vec3_substract(p[i].v01.c3.vec3d, lcomp->lights[j].pos.c3.vec3d);
	a.tmp_n = vec3_normalize(a.tmp);
	p[i].v_light.a[0] += (lcomp->lights[j].intensity / (vec3_magnitude(a.tmp)
		* lcomp->lights[j].fallof)) * (vec3_dot(a.tmp_n, p[i].normal) + 1.0)
			/ 2.0;
	p[i].v_light.a[0] = mf_clamp_double(p[i].v_light.a[0], 0, 1.0);
	a.tmp = vec3vec3_substract(p[i].v12.c3.vec3d, lcomp->lights[j].pos.c3.vec3d);
	a.tmp_n = vec3_normalize(a.tmp);
	p[i].v_light.a[1] += (lcomp->lights[j].intensity / (vec3_magnitude(a.tmp)
		* lcomp->lights[j].fallof)) * (vec3_dot(a.tmp_n, p[i].normal) + 1.0)
			/ 2.0;
	p[i].v_light.a[1] = mf_clamp_double(p[i].v_light.a[1], 0, 1.0);
	a.tmp = vec3vec3_substract(p[i].v20.c3.vec3d, lcomp->lights[j].pos.c3.vec3d);
	a.tmp_n = vec3_normalize(a.tmp);
	p[i].v_light.a[2] += (lcomp->lights[j].intensity / (vec3_magnitude(a.tmp)
		* lcomp->lights[j].fallof)) * (vec3_dot(a.tmp_n, p[i].normal) + 1.0)
			/ 2.0;
	p[i].v_light.a[2] = mf_clamp_double(p[i].v_light.a[2], 0, 1.0);
}

void	calculate_lighting(t_polygon *p, int count, t_light_comp *lcomp)
{
	int			i;
	int			j;
	t_2vec3d	a;

	i = -1;
	while (++i < count)
	{
		j = -1;
		while (lcomp && ++j < lcomp->light_count)
		{
			a.tmp = vec3vec3_substract(p[i].v01.c3.vec3d,
				lcomp->lights[j].pos.c3.vec3d);
			a.tmp_n = vec3_normalize(a.tmp);
			if (lcomp->lights[j].type == POINT_LIGHT)
				i_calculate(p, i, j, lcomp, a);
			if (lcomp->lights[j].type == DIRECTIONAL_LIGHT)
				j_calculate(p, i, j, lcomp, a);
		}
		if (!lcomp || lcomp->light_count == 0)
			p[i].v_light = (t_vec3d){.a = {1, 1, 1}};
	}
}
