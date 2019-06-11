/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_at.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:20:26 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/11 12:52:19 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static void quick_inverse(double mat[4][4])
{
    double  tmp[4][4];
    int     i;

    i = -1;
    while (++i < 3)
    {
        tmp[i][0] = mat[0][i];
        tmp[i][1] = mat[1][i];
        tmp[i][2] = mat[2][i];
        tmp[i][3] = mat[0][3] * tmp[i][0] + mat[1][3] * tmp[i][1] + mat[2][3] * tmp[i][2];
    }
    tmp[3][0] = 0.0;
    tmp[3][1] = 0.0;
    tmp[3][2] = 0.0;
    tmp[3][3] = 1.0;
    mat4_copy(mat, tmp);
}

void    look_at(double from[3], double to[3], double tmp_up[3], double res[4][4])
{
    double  forward[3];
    double  right[3];
    double  up[3];
    double  tmp[3];
    int     i;

    vec3vec3_substract(from, to, tmp);
    vec3_normalize(tmp, forward);
    vec3vec3_crossproduct(tmp_up, forward, tmp);
    vec3_normalize(tmp, right);
    vec3vec3_crossproduct(forward, right, up);
    mat4_init(res);
    i = -1;
    while (++i < 3)
    {
        res[i][0] = right[i];
        res[i][1] = up[i];
        res[i][2] = forward[i];
        res[i][3] = -from[i]; /// 2.0; //divide by two if self created
    }
    quick_inverse(res);
}
