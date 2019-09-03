/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_update_editor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:49:51 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/03 15:57:44 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		modifier_update_editor(t_mesh *mesh, t_editor_interface *editor)
{
	editor->is_physics = (mesh->walls == NULL) ? FALSE : TRUE;
	update_is_physics(editor);
	if (mesh->walls)
		editor->wall_friction = mesh->walls->friction;
	update_wall_friction(editor);
	editor->alpha = mesh->polygons->transparency;
	update_alpha(editor);
}