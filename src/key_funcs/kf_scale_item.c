/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_scale_item.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 13:43:11 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/03 13:28:57 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_scale_item(void *param)
{
	t_e		*e;

	e = param;
	if (!e->editor.item_placer)
		return ;
	if (e->editor.is_modified)
	{
		if (e->input_map.mouse.wheel_scrol.n.y > 0)
			e->editor.item_placer->matrix = mat4_scale(e->
				editor.item_placer->matrix, 1.1, 1.1, 1.1);
		else if (e->input_map.mouse.wheel_scrol.n.y < 0)
			e->editor.item_placer->matrix = mat4_scale(e->
				editor.item_placer->matrix,
				0.9, 0.9, 0.9);
		mesh_delete_physics(e->editor.item_placer);
		mesh_add_physics(e->editor.item_placer,
		(e->editor.wall_friction_is_auto) ? -1 : e->editor.wall_friction);
	}
	else
	{
		if (e->input_map.mouse.wheel_scrol.n.y > 0)
			e->editor.item_scale_mat = mat4_scale(e->editor.item_scale_mat,
				1.1, 1.1, 1.1);
		else if (e->input_map.mouse.wheel_scrol.n.y < 0)
			e->editor.item_scale_mat = mat4_scale(e->editor.item_scale_mat,
				0.9, 0.9, 0.9);
	}
}
