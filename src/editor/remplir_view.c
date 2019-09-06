/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remplir_view.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:18:09 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/06 11:08:52 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

void		remplir_preview(t_editor_interface *editor_interface)
{
	t_mat4d		mat4_tmp;

	gthread_get(GTHREAD_PREVIEW);
	if (editor_interface->item_placer)
	{
		mat4_tmp = ((t_mesh *)editor_interface->item_placer)->matrix;
		((t_mesh *)editor_interface->item_placer)->matrix = editor_interface->
			preview_mat;
		render_preview(editor_interface->item_placer, editor_interface->
			preview_container.texture,
		(t_vec2i){.a = {editor_interface->preview_container.texture->w,
			editor_interface->preview_container.texture->h}});
		((t_mesh *)editor_interface->item_placer)->matrix = mat4_tmp;
		editor_interface->preview_container.need_redraw = 1;
	}
}

static void	remplir_view_with_crosshair(t_editor_interface *editor_interface,
		int color)
{
	int		i;
	int		y;

	i = editor_interface->view_container.texture->w / 2 - 5;
	y = editor_interface->view_container.texture->h / 2;
	while (i < editor_interface->view_container.texture->w / 2 + 5)
	{
		((int *)(editor_interface->view_container.texture->pixels))[y
			* editor_interface->view_container.texture->w + i] = color;
		i++;
	}
	i = editor_interface->view_container.texture->w / 2;
	y = editor_interface->view_container.texture->h / 2 - 5;
	while (y < editor_interface->view_container.texture->h / 2 + 5)
	{
		((int *)(editor_interface->view_container.texture
			->pixels))[y
			* editor_interface->view_container.texture->w + i] = color;
		y++;
	}
}

static void	remplir_3dview_sub(t_editor_interface *ei, t_e *e)
{
	gthread_get(GTHREAD_EDITOR);
	ei->view_container.need_redraw = 1;
	render_editor_view(&e->world, ei);
	mat4_init(&ei->item_mat);
}

static void	remplir_3dview_sub2(t_editor_interface *ei)
{
	t_vec3d		tmp;
	double		nr;
	t_mat4d		m;

	ei->item_placer->matrix = ei->item_scale_mat;
	nr = get_mesh_radius(ei->item_placer) + 15;
	tmp = vec3vec3_substract(ei->editor_cam.pos,
	vec3scalar_multiply(ei->editor_cam.view_dir, nr > 15 ? nr : 15));
	m = quat_to_mat4d(ei->item_rotation);
	ei->item_placer->matrix = mat4mat4_multiply(((t_mesh *)
		ei->item_placer)->matrix, m);
	ei->item_placer->matrix = mat4_translate(((t_mesh *)
		ei->item_placer)->matrix, tmp.n.x, tmp.n.y, tmp.n.z);
	render_mesh(ei->item_placer, &ei->editor_cam,
		ei->view_container.texture, NULL);
}

void		remplir_3dview(t_editor_interface *ei, t_e *e)
{
	remplir_3dview_sub(ei, e);
	if (ei->item_placer)
	{
		if (!ei->is_modified)
		{
			remplir_3dview_sub2(ei);
		}
		else
		{
			render_wireframe_mesh(ei->item_placer, &ei->editor_cam,
						ei->view_container.texture, WIREFRAME_COLOR);
		}
	}
	if (ei->is_modified)
		remplir_view_with_crosshair(ei, 0xffff0000);
	else
		remplir_view_with_crosshair(ei, 0xffffffff);
}
