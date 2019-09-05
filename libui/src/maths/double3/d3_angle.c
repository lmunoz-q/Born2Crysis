/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d3_angle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:29:19 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:29:20 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_maths.h>
#include <math.h>

double	d3_angle_normals(t_double3 a, t_double3 b, t_double3 *axis)
{
	if (axis)
		*axis = d3_cross_product(a, b);
	return (acos(d3_dot_product(a, b)));
}

double	d3_angle(t_double3 a, t_double3 b, t_double3 *axis)
{
	return (d3_angle_normals(d3_normalize(a), d3_normalize(b), axis));
}
