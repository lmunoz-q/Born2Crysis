/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_editor_view.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 20:55:16 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/14 18:35:22 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void 	render_editor_view(t_world *world, t_editor_interface *ei)
{
	t_vec3d		look_dir;

	look_dir = vec3vec3_add(ei->editor_cam.pos, ei->editor_cam.view_dir);
	mf_memset(get_zbuff(), 0, ei->view_container.texture->w * ei->view_container.texture->h * sizeof(double));
	ei->editor_cam.view_matrix = look_at(ei->editor_cam.pos, look_dir, (t_vec3d){.a = {0, -1, 0}});
	openworld_render(world, &ei->editor_cam, ei->view_container.texture);
	skybox_set_pos(world->skybox, ei->editor_cam.pos);
	render_object(world->skybox, &ei->editor_cam, ei->view_container.texture, NULL);
	draw_transparent(ei->view_container.texture);
}