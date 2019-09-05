/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d3_normalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:29:32 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:29:33 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_maths.h>
#include <math.h>

#include <stdio.h>

t_double3	d3_normalize(t_double3 v)
{
	double	m;

	m = 1.0 / sqrt(d3_dot_product(v, v));
	return ((t_double3){.x = v.x * m, .y = v.y * m, .z = v.z * m});
}
