/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_to_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:00:26 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/12 14:47:33 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		world_to_view(t_polygon *p, int count, t_mat4d view_mat)
{
	int i;

	i = -1;
	while (++i < count)
	{
		p[i].v01 = mat4vec4_multiply(view_mat, p[i].v01);
		p[i].v12 = mat4vec4_multiply(view_mat, p[i].v12);
		p[i].v20 = mat4vec4_multiply(view_mat, p[i].v20);
	}
}
