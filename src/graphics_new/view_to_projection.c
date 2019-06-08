/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_to_projection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 00:04:36 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/09 00:22:43 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	perspective_divide(t_polygon *p, int width, int height)
{
	vec2scalar_divide(p->v01, p->v01[2], p->v01);
	vec2scalar_divide(p->v12, p->v12[2], p->v12);
	vec2scalar_divide(p->v20, p->v20[2], p->v20);
	p->v01[0] = (p->v01[0] + 1.0) * (double)(width / 2.0);
	p->v12[0] = (p->v12[0] + 1.0) * (double)(width / 2.0);
	p->v20[0] = (p->v20[0] + 1.0) * (double)(width / 2.0);
	p->v01[1] = (p->v01[1] + 1.0) * (double)(height / 2.0);
	p->v12[1] = (p->v12[1] + 1.0) * (double)(height / 2.0);
	p->v20[1] = (p->v20[1] + 1.0) * (double)(height / 2.0);
	vec2scalar_divide(p->v01_uv, p->v01[2], p->v01_uv);
	vec2scalar_divide(p->v12_uv, p->v12[2], p->v12_uv);
	vec2scalar_divide(p->v20_uv, p->v20[2], p->v20_uv);
	p->v01[2] = -1.0 / p->v01[2];
	p->v12[2] = -1.0 / p->v12[2];
	p->v20[2] = -1.0 / p->v20[2];
}

void		view_to_projection(t_polygon *p, int count, double proj_mat[4][4], SDL_Surface *surface)
{
	int i;

	i = -1;
	while (++i < count)
	{
		if (p[i].tex_id == -1)
			continue ;
		mat4vec4_multiply(proj_mat, p[i].v01, p[i].v01);
		mat4vec4_multiply(proj_mat, p[i].v12, p[i].v12);
		mat4vec4_multiply(proj_mat, p[i].v20, p[i].v20);
		perspective_divide(&p[i], surface->w, surface->h);
		
	}
}