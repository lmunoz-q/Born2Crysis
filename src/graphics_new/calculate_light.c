/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:55:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/21 22:11:08 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	calculate_lighting(t_polygon *p, int count, t_light_comp *lcomp)
{
	int		i;
	int		j;
	double	tmp[3];
	double	tmp_n[3];

	i = -1;
	while (++i < count)
	{
		j = -1;
		while (++j < lcomp->light_count)
		{
			if (lcomp->lights[j].type == POINT_LIGHT)
			{
				vec3vec3_substract(p[i].v01, lcomp->lights[j].pos, tmp);
				vec3_normalize(tmp, tmp_n);
				p[i].v_light[0] += (lcomp->lights[j].intensity / (vec3_magnitude(tmp) * 4.0)) * (vec3_dot(tmp_n, p[i].normal) + 1.0) / 2.0;
				p[i].v_light[0] = mf_clamp_double(p[i].v_light[0], 0, 1.0);
				vec3vec3_substract(p[i].v12, lcomp->lights[j].pos, tmp);
				vec3_normalize(tmp, tmp_n);
				p[i].v_light[1] += (lcomp->lights[j].intensity / (vec3_magnitude(tmp) * 4.0)) * (vec3_dot(tmp_n, p[i].normal) + 1.0) / 2.0;
				p[i].v_light[1] = mf_clamp_double(p[i].v_light[1], 0, 1.0);
				vec3vec3_substract(p[i].v20, lcomp->lights[j].pos, tmp);
				vec3_normalize(tmp, tmp_n);
				p[i].v_light[2] += (lcomp->lights[j].intensity / (vec3_magnitude(tmp) * 4.0)) * (vec3_dot(tmp_n, p[i].normal) + 1.0) / 2.0;
				p[i].v_light[2] = mf_clamp_double(p[i].v_light[2], 0, 1.0);
			}
			if (lcomp->lights[j].type == DIRECTIONAL_LIGHT)
			{
				vec3vec3_substract(p[i].v01, lcomp->lights[j].pos, tmp);
				vec3_normalize(tmp, tmp_n);
				p[i].v_light[0] += (lcomp->lights[j].intensity / (vec3_magnitude(tmp) * 3.0)) * ((vec3_dot(lcomp->lights[j].dir, p[i].normal) - 1.0) / -2.0) * vec3_dot(tmp_n, p[i].normal);
				p[i].v_light[0] = mf_clamp_double(p[i].v_light[0], 0, 1.0);
				vec3vec3_substract(p[i].v12, lcomp->lights[j].pos, tmp);
				vec3_normalize(tmp, tmp_n);
				p[i].v_light[1] += (lcomp->lights[j].intensity / (vec3_magnitude(tmp) * 3.0)) * ((vec3_dot(lcomp->lights[j].dir, p[i].normal) - 1.0) / -2.0) * vec3_dot(tmp_n, p[i].normal);
				p[i].v_light[1] = mf_clamp_double(p[i].v_light[1], 0, 1.0);
				vec3vec3_substract(p[i].v20, lcomp->lights[j].pos, tmp);
				vec3_normalize(tmp, tmp_n);
				p[i].v_light[2] += (lcomp->lights[j].intensity / (vec3_magnitude(tmp) * 3.0)) * ((vec3_dot(lcomp->lights[j].dir, p[i].normal) - 1.0) / -2.0) * vec3_dot(tmp_n, p[i].normal);
				p[i].v_light[2] = mf_clamp_double(p[i].v_light[2], 0, 1.0);
			}
		}
		if (lcomp->light_count == 0)
			vec3_copy(p[i].v_light, (double [3]){1, 1, 1});
	}
}
