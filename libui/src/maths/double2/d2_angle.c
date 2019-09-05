/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d2_angle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:28:44 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:28:45 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_maths.h>
#include <math.h>

double	d2_angle_normals(t_double2 a, t_double2 b)
{
	return (acos(d2_dot_product(a, b)));
}

double	d2_angle(t_double2 a, t_double2 b)
{
	return (d2_angle_normals(d2_normalize(a), d2_normalize(b)));
}
