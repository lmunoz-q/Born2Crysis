/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remplir_view.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:18:09 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/30 13:21:10 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		remplir_preview(t_editor_interface *editor_interface, t_e *e)
{
	t_mat4d		mat4_tmp;
	
	(void)e;
	gthread_get(GTHREAD_PREVIEW);
	if (editor_interface->item_placer)
	{
		mat4_tmp = ((t_mesh *)editor_interface->item_placer)->matrix;
		((t_mesh *)editor_interface->item_placer)->matrix = editor_interface->preview_mat;
		render_preview(editor_interface->item_placer, editor_interface->preview_container.texture,
		(t_vec2i){.a = {editor_interface->preview_container.texture->w, editor_interface->preview_container.texture->h}});
		((t_mesh *)editor_interface->item_placer)->matrix = mat4_tmp;
		editor_interface->preview_container.need_redraw = 1;
	}
}

static void	remplir_view_with_crosshair(t_editor_interface *editor_interface, t_e *e)
{
	int			i;
	int			y;

	i = editor_interface->view_container.texture->w / 2 - 5;
	y = editor_interface->view_container.texture->h / 2;
	while (i < editor_interface->view_container.texture->w / 2 + 5)
	{
		((int *)(editor_interface->view_container.texture->pixels))[y * editor_interface->view_container.texture->w + i] = 0xffffffff;
		i++;
	}
	i = editor_interface->view_container.texture->w / 2;
	y = editor_interface->view_container.texture->h / 2 - 5;
	while (y < editor_interface->view_container.texture->h / 2 + 5)
	{
		((int *)(editor_interface->view_container.texture
			->pixels))[y * editor_interface->view_container.texture->w + i]
			= 0xffffffff;
		y++;
	}
}

void		remplir_3dview(t_editor_interface *editor_interface, t_e *e)
{
	t_vec3d		tmp;
	double		new_radius;
	t_mat4d		m;

	gthread_get(GTHREAD_EDITOR);
	editor_interface->view_container.need_redraw = 1;
	render_editor_view(&e->world, editor_interface);
	mat4_init(&editor_interface->item_mat);
	if (!editor_interface->item_placer)
		return ;
	editor_interface->item_placer->matrix = editor_interface->item_scale_mat;
	new_radius = get_mesh_radius(editor_interface->item_placer) + 15;
	tmp = vec3vec3_substract(editor_interface->editor_cam.pos,
	vec3scalar_multiply(editor_interface->editor_cam.view_dir,
		(new_radius > 15) ? new_radius : 15));
	m = quat_to_mat4d(editor_interface->item_rotation);
	editor_interface->item_placer->matrix = mat4mat4_multiply(((t_mesh *)editor_interface->item_placer)->matrix , m);
	editor_interface->item_placer->matrix = mat4_translate(((t_mesh *)editor_interface->item_placer)->matrix, tmp.n.x, tmp.n.y, tmp.n.z);
	render_mesh(editor_interface->item_placer, &editor_interface->editor_cam, editor_interface->view_container.texture, NULL);
	remplir_view_with_crosshair(editor_interface, e);
}
