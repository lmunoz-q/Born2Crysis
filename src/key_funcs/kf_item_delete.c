/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_item_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 19:05:10 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/02 23:15:04 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	i_get_target_mesh(t_e *e, t_vec4d pos, t_sector **src, double dot)
{
	int32_t i;
	int32_t j;

	i = -1;
	while (++i < e->world.sectornum)
	{
		j = -1;
		while (++j < e->world.sectors[i].meshnum)
		{
			vec4_init(&pos);
			pos = mat4vec4_multiply(e->world.sectors[i].mesh[j].matrix, pos);
			if (vec3vec3_dist(pos.c3.vec3d, e->editor.editor_cam.pos) > ZFAR)
				continue;
			if (vec3_dot(e->editor.editor_cam.view_dir,
				vec3_normalize(vec3vec3_substract(pos.c3.vec3d,
					e->editor.editor_cam.pos))) < dot)
			{
				*src = &e->world.sectors[i];
				dot = vec3_dot(e->editor.editor_cam.view_dir,
					vec3_normalize(vec3vec3_substract(pos.c3.vec3d,
						e->editor.editor_cam.pos)));
				e->editor.selected_mesh = &e->world.sectors[i].mesh[j];
			}
		}
	}
}

void	get_target_mesh(t_e *e)
{
	t_vec4d		pos;
	t_sector	*src;
	double		dot;

	dot = 0;
	src = NULL;
	vec4_init(&pos);
	i_get_target_mesh(e, pos, &src, dot);
	if (e->editor.selected_mesh)
	{
		light_delete(&src->lights, ((t_mesh *)e->editor.selected_mesh)->
						light_id);
		if (mesh_delete(&src->mesh, src->meshnum, e->editor.selected_mesh
		- src->mesh))
			src->meshnum--;
	}
}

void	kf_item_delete(void *param)
{
	t_e	*e;

	e = param;
	if (!e->editor.is_in_view)
		return ;
	if (e->editor.is_modified)
	{
		e->editor.item_placer = NULL;
		return ;
	}
	e->editor.dist = ZFAR;
	e->editor.selected_mesh = NULL;
	get_target_mesh(e);
}
