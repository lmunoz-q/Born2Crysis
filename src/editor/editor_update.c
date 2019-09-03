/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 23:36:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/03 13:16:01 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	editor_update(t_e *e, t_editor_interface *editor_interface)
{
	editor_interface->preview_mat = mat4_rotate_pitch(editor_interface->
		preview_mat, 1);
	update_sector_physics(e);
	if (editor_interface->is_modified && editor_interface->item_placer
	&& e->editor.alpha != e->editor.item_placer->polygons->transparency)
	{
		polygons_set_trans(editor_interface->item_placer->polygons,
							editor_interface->item_placer->polygonnum,
							editor_interface->alpha);
	}
	return (0);
}
