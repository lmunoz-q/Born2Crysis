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
# define ZNEAR	1

typedef struct	s_camera
{
	double		pos[3];
	double		view_dir[3];
	double		view_matrix[4][4];
	double		projection_matrix[4][4];
}				t_camera;

void		init_camera(t_camera *cam, t_vec2i win_size);
void		look_at(double from[3], double to[3], double tmp_up[3], double res[4][4]);
void		generate_projection_matrix(double proj_matrix[4][4], t_vec2i size);

#endif
