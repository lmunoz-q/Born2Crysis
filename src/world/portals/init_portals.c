/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_portals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 22:15:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/07 19:46:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include <stdio.h>

void	calculate_portal_normal(t_mesh	*m, double normal[3])
{
	double	tmp1[4];
	double	tmp2[4];
	double	tmp3[4];

	if (m->polygonnum)
	{
		mat4vec4_multiply(m->matrix, m->polygons->v01, tmp1);
		mat4vec4_multiply(m->matrix, m->polygons->v12, tmp2);
		mat4vec4_multiply(m->matrix, m->polygons->v20, tmp3);
		vec3p_get_normal(tmp1, tmp2, tmp3, normal);
	}
}

void	init_portals(t_world *world)
{
	int i;
	int j;

	i = -1;
	while (++i < world->sectornum)
	{
		j = -1;
		while (++j < world->sectors[i].meshnum)
		{
			if (world->sectors[i].mesh[j].sector_id == -1)
				continue ;
			calculate_portal_normal(&world->sectors[i].mesh[j],
									world->sectors[i].mesh[j].portal_normal);
		}
	}
}
