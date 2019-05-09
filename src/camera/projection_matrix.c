/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:25:10 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/09 18:26:17 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void    generate_projection_matrix(double proj_matrix[4][4], t_vec2i size)
{
    double fovr;

    fovr = (1.0 / tan(FOV * 0.5 * M_PI / 180.0));
    proj_matrix[0][0] = ((double)size.y / (double)size.x) * fovr;
    proj_matrix[1][1] = fovr;
    proj_matrix[2][2] = ZFAR / (ZFAR - ZNEAR);
    proj_matrix[3][2] = (-ZFAR * ZNEAR) / (ZFAR - ZNEAR);
    proj_matrix[3][2] = 1;
    proj_matrix[3][3] = 0;
}
