/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mfmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 22:23:16 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/30 12:56:27 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MFMATH_H
# define MFMATH_H

# include <math.h>
# include "math_types.h"

typedef struct	s_intrect
{
	int			x;
	int			y;
	int			w;
	int			h;
}				t_intrect;

/*
** MATRIX OPERATIONS
*/

void			mat4_init(t_mat4d *mat);
void			mat3_init(t_mat3d *mat);
void			mat2_init(t_mat2d *mat);

void			mat4_clear(t_mat4d *mat);
void			mat3_clear(t_mat3d *mat);
void			mat2_clear(t_mat2d *mat);

t_mat4d			mat4_translate(t_mat4d mat, double x, double y, double z);
t_mat3d			mat3_translate(t_mat3d mat, double x, double y);

t_mat4d			mat4_scale(t_mat4d mat, double x, double y, double z);
t_mat3d			mat3_scale(t_mat3d mat, double x, double y);

t_mat4d			mat4_rotate_yaw(t_mat4d mat, double angle);
t_mat4d			mat4_rotate_pitch(t_mat4d mat, double angle);
t_mat4d			mat4_rotate_roll(t_mat4d mat, double angle);

t_mat3d			mat3_rotate(t_mat3d mat, double angle);

/*
** MATRIX & MATRIX OPERATIONS
*/

t_mat4d			mat4mat4_multiply(t_mat4d mat1, t_mat4d mat2);
t_mat3d			mat3mat3_multiply(t_mat3d mat1, t_mat3d mat2);
t_mat2d			mat2mat2_multiply(t_mat2d mat1, t_mat2d mat2);

/*
** VECTOR OPERATIONS
*/

int				vec4_eqal(t_vec4d vec1, t_vec4d vec2);
int				vec3_eqal(t_vec3d vec1, t_vec3d vec2);
int				vec2_eqal(t_vec2d vec1, t_vec2d vec2);

void			vec4_init(t_vec4d *vec);
void			vec3_init(t_vec3d *vec);
void			vec2_init(t_vec2d *vec);

void			vec4_clear(t_vec4d *vec);
void			vec3_clear(t_vec3d *vec);
void			vec2_clear(t_vec2d *vec);

double			vec4_magnitude(t_vec4d vector);
double			vec3_magnitude(t_vec3d vector);
double			vec2_magnitude(t_vec2d vector);

t_vec4d			vec4_normalize(t_vec4d vector);
t_vec3d			vec3_normalize(t_vec3d vector);
t_vec2d			vec2_normalize(t_vec2d vector);

double			vec4_dot(t_vec4d vec, t_vec4d vec2);
double			vec3_dot(t_vec3d vec, t_vec3d vec2);
double			vec2_dot(t_vec2d vec, t_vec2d vec2);

t_vec4d			vec4scalar_multiply(t_vec4d vec, double scalar);
t_vec3d			vec3scalar_multiply(t_vec3d vec, double scalar);
t_vec2d			vec2scalar_multiply(t_vec2d vec, double scalar);

t_vec4d			vec4scalar_add(t_vec4d vec, double scalar);
t_vec3d			vec3scalar_add(t_vec3d vec, double scalar);
t_vec2d			vec2scalar_add(t_vec2d vec, double scalar);

t_vec4d			vec4scalar_divide(t_vec4d vec, double scalar);
t_vec3d			vec3scalar_divide(t_vec3d vec, double scalar);
t_vec2d			vec2scalar_divide(t_vec2d vec, double scalar);

/*
** VECTOR & VECTOR OPERATIONS
*/

t_vec4d			vec4vec4_substract(t_vec4d minuend, t_vec4d subtrahend);
t_vec3d			vec3vec3_substract(t_vec3d minuend, t_vec3d subtrahend);
t_vec2d			vec2vec2_substract(t_vec2d minuend, t_vec2d subtrahend);

t_vec4d			vec4vec4_add(t_vec4d addend, t_vec4d augend);
t_vec3d			vec3vec3_add(t_vec3d addend, t_vec3d augend);
t_vec2d			vec2vec2_add(t_vec2d addend, t_vec2d augend);

t_vec4d			vec4vec4_divide(t_vec4d dividend, t_vec4d divisor);
t_vec3d			vec3vec3_divide(t_vec3d dividend, t_vec3d divisor);
t_vec2d			vec2vec2_divide(t_vec2d dividend, t_vec2d divisor);

double			vec3vec3_dist(t_vec3d v1, t_vec3d v2);
double			vec2vec2_dist(t_vec2d v1, t_vec2d v2);

t_vec4d			vec4vec4_multiply(t_vec4d vec1, t_vec4d vec2);
t_vec3d			vec3vec3_multiply(t_vec3d vec1, t_vec3d vec2);
t_vec2d			vec2vec2_multiply(t_vec2d vec1, t_vec2d vec2);

t_vec4d			vec4vec4_crossproduct(t_vec4d v1, t_vec4d v2);
t_vec3d			vec3vec3_crossproduct(t_vec3d v1, t_vec3d v2);

t_vec4d			vec3vec4_convert(t_vec3d vec);

double			vec4vec4_angle(t_vec4d v1, t_vec4d v2);
double			vec3vec3_angle(t_vec3d v1, t_vec3d v2);
double			vec2vec2_angle(t_vec2d v1, t_vec2d v2);

/*
** MATRIX & VECTOR OPERATIONS
*/

t_vec4d			mat4vec4_multiply(t_mat4d mat, t_vec4d vec);
t_vec3d			mat3vec3_multiply(t_mat3d mat, t_vec3d vec);
t_vec2d			mat2vec2_multiply(t_mat2d mat, t_vec2d vec);

/*
** 3D MATH FUNCS
*/

/*
** returns shortest distance between point and plane.(normal must be normalized)
*/

double			dist_pointplane(t_vec3d plane_n, t_vec3d plane_p,
								t_vec3d point);

/*
** Calculates the normal of three points in 3d space
*/

t_vec3d			vec3p_get_normal(t_vec3d p1, t_vec3d p2, t_vec3d p3);

/*
** QUATERNIONS
*/

t_vec4d			quat_rotator(t_vec3d axis, double rad);

t_vec4d			quat_multiply(t_vec4d q1, t_vec4d q2);

t_vec4d			quat_inverse(t_vec4d q);

t_mat3d			quat_to_mat3d(t_vec4d q);

t_mat4d			quat_to_mat4d(t_vec4d q);

#endif
