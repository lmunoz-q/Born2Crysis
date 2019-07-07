/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_clip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:03:22 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/06 20:53:17 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void		cull_aginst_plane(t_mesh *mesh, int mn, double p[3], double n[3])
{
	int		i;
	double	pos[4];

	i = -1;
	while (++i < mn)
	{
		if (!mesh[i].active)
			continue ;
		mat4vec4_multiply(mesh[i].matrix, (double [4]){0, 0, 0, 1}, pos);
		if (dist_pointplane(n, p, pos) > mesh->radius)
			mesh->active = FALSE;
	}
}

static void		init_portal_cull(t_mesh *mesh, int meshnum)
{
	int i;

	i = -1;
	while (++i < meshnum)
		mesh[i].active = TRUE;
}

void		make_portal_plane(t_mesh *portal, double p[3], double n[3])
{
	int		i;
	double	p1[4];
	double	p2[4];

	i = -1;
	while (++i < portal->polygonnum - 1)
	{
		
	}
}

void		portal_cull(t_mesh *mesh, int meshenum, t_mesh *portal)
{
	init_portal_cull(mesh, meshenum);

}