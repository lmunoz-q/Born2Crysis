/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_item_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 19:05:10 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/21 18:25:29 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

static void	get_target_mesh(t_e *e)
{
	t_vec4d		pos;
	t_sector	*src;
	double		dot;
	Uint32		i;
	Uint32		j;

	dot = 0;
	i = (Uint32)-1;
	src = NULL;
	while (++i < e->world.sectornum)
	{
		j = (Uint32)-1;
		while (++j < e->world.sectors[i].meshnum)
		{
			vec4_init(&pos);
			pos = mat4vec4_multiply(e->world.sectors[i].mesh[j].matrix, pos);
			if (vec3vec3_dist(pos.c3.vec3d, e->editor.editor_cam.pos) > ZFAR)
				return ;
			if (vec3_dot(e->editor.editor_cam.view_dir, vec3_normalize(vec3vec3_substract(pos.c3.vec3d, e->editor.editor_cam.pos))) < dot)
			{
				src = &e->world.sectors[i];
				dot = vec3_dot(e->editor.editor_cam.view_dir, vec3_normalize(vec3vec3_substract(pos.c3.vec3d, e->editor.editor_cam.pos)));
				e->editor.selected_mesh = &e->world.sectors[i].mesh[j];
			}
		}
	}
	if (e->editor.selected_mesh)
	{
		if (mesh_delete(&src->mesh, src->meshnum, e->editor.selected_mesh - src->mesh))
			src->meshnum--;
	}
		
}

void		kf_item_delete(void *param)
{
	t_e	 *e;

	e = param;
	if (!e->editor.is_in_view)
		return ;
	e->editor.dist = ZFAR;
	e->editor.selected_mesh = NULL;
	get_target_mesh(e);
}
