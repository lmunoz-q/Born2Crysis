/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_portals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 22:15:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 19:48:23 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include <stdio.h>

void	calculate_portal_normal(t_mesh *m, t_vec3d *normal)
{
	t_vec4d	tmp1;
	t_vec4d	tmp2;
	t_vec4d	tmp3;

	if (m->polygonnum)
	{
		tmp1 = mat4vec4_multiply(m->matrix, m->polygons->v01);
		tmp2 = mat4vec4_multiply(m->matrix, m->polygons->v12);
		tmp3 = mat4vec4_multiply(m->matrix, m->polygons->v20);
		*normal = vec3p_get_normal(tmp1.c3.vec3d, tmp2.c3.vec3d, tmp3.c3.vec3d);
	}
}

void	init_portals(t_world *world)
{
	int32_t i;
	int32_t j;

	i = -1;
	while (++i < world->sectornum)
	{
		j = -1;
		while (++j < world->sectors[i].meshnum)
		{
			if (world->sectors[i].mesh[j].sector_id == -1)
				continue ;
			
			calculate_portal_normal(&world->sectors[i].mesh[j],
									&world->sectors[i].mesh[j].portal_normal);
		}
	}
}
