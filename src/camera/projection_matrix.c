/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:25:10 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/11 17:50:40 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
# include <stdio.h>

void	generate_projection_matrix(t_mat4d *proj_matrix, t_vec2i size)
{
	double fovr;

	mat4_init(proj_matrix);
	fovr = (1.0 / tan(FOV * 0.5 * M_PI / 180.0));
	proj_matrix->a[0][0] = ((double)size.n.y / (double)size.n.x) * fovr;
	proj_matrix->a[1][1] = fovr;
	proj_matrix->a[2][2] = ZFAR / (ZFAR - ZNEAR);
	proj_matrix->a[3][2] = (-ZFAR * ZNEAR) / (ZFAR - ZNEAR);
	proj_matrix->a[3][2] = 1;
	proj_matrix->a[3][3] = 0;
}
