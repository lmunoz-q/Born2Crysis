/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d2_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:28:59 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:28:59 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_maths.h>
#include <math.h>

t_double2	d2_rotate_cs(t_double2 v, double cos_a, double sin_a)
{
	return ((t_double2){.x = v.x * cos_a - v.y * sin_a,
						.y = v.x * sin_a + v.y * cos_a});
}

t_double2	d2_rotate(t_double2 v, double a)
{
	return (d2_rotate_cs(v, cos(a), sin(a)));
}
