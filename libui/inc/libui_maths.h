/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:31:32 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/29 22:29:47 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_MATHS_H
# define LIBUI_MATHS_H

# include <SDL2/SDL_rect.h>

typedef struct	s_double3
{
	double		x;
	double		y;
	double		z;
}				t_double3;

typedef struct	s_double2
{
	double		x;
	double		y;
}				t_double2;

typedef struct	s_double3_2
{
	t_double3	a;
	t_double3	b;
}				t_double3_2;

typedef struct	s_double2_2
{
	t_double2	a;
	t_double2	b;
}				t_double2_2;

typedef struct	s_int2
{
	int			x;
	int			y;
}				t_int2;

t_double2		d3_to_d2(t_double3 v);
t_double3		d2_to_d3(t_double2 v);
t_int2			d2_to_i2(t_double2 v);

t_double3		d3_normalize(t_double3 v);
t_double3		d3_cross_product(t_double3 a, t_double3 b);
double			d3_dot_product(t_double3 a, t_double3 b);
double			d3_angle_normals(t_double3 a, t_double3 b, t_double3 *axis);
double			d3_angle(t_double3 a, t_double3 b, t_double3 *axis);

t_double2		d2_normalize(t_double2 v);
double			d2_cross_product(t_double2 a, t_double2 b);
double			d2_cross_product_flat(double ax, double ay, double bx,
										double by);
double			d2_dot_product(t_double2 a, t_double2 b);
double			d2_angle_normals(t_double2 a, t_double2 b);
double			d2_angle(t_double2 a, t_double2 b);
t_double2		d2_substract(t_double2 a, t_double2 b);
t_double2		d2_scale(t_double2 v, double scalar);
t_double2		d2_add(t_double2 a, t_double2 b);

t_double2		d2_intersect(t_double2 l1_start, t_double2 l1_end,
							t_double2 l2_start, t_double2 l2_end);
t_double2		d2_rotate_cs(t_double2 v, double cos_a, double sin_a);
t_double2		d2_rotate(t_double2 v, double a);

int				libui_sdl_rect_is_inside(SDL_Rect rect1, SDL_Rect rect2);

#endif
