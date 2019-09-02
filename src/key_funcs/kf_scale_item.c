/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_scale_item.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 13:43:11 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/02 23:19:39 by mfischer         ###   ########.fr       */
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
			e->editor.item_placer->matrix = mat4_scale(e->editor
				.item_placer->matrix,
				1.1, 1.1, 1.1);
		else if (e->input_map.mouse.wheel_scrol.n.y < 0)
			e->editor.item_placer->matrix = mat4_scale(e->editor
				.item_placer->matrix,
				0.9, 0.9, 0.9);
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
