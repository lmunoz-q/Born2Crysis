/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 00:02:33 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/11 00:21:21 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	recursive_object_render(t_camera *cam, t_libui_window *win,
									t_object *object, double mat[4][4])
{
	double mat_tmp[4][4];

	mat4mat4_multiply(mat, object->matrix, mat_tmp);
	render_polygons(object->polygons, mat_tmp, win, cam);
	if (object->sub_object)
		recursive_object_render(cam, win, object->sub_object, mat_tmp);
}

void		render_object(t_camera *cam, t_libui_window *win, t_object *object)
{
	double mat[4][4];

	mat4_init(mat);
	recursive_object_render(cam, win, object, mat);
}