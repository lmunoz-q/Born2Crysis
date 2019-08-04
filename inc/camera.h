/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:06:37 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/19 10:24:48 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "mflib.h"

# define FOV	90
# define ZFAR	10000.0
# define ZNEAR	0.5

typedef struct	s_camera
{
	t_vec3d		pos;
	t_vec3d		view_dir;
	t_mat4d		view_matrix;
	t_mat4d		projection_matrix;
}				t_camera;

void		init_camera(t_camera *cam, t_vec2i win_size);
t_mat4d		look_at(t_vec3d from, t_vec3d to, t_vec3d tmp_up);
void		generate_projection_matrix(t_mat4d *proj_matrix, t_vec2i size);

#endif
