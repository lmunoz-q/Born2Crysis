/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d2_normalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:28:56 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:28:57 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_maths.h>
#include <math.h>

t_double2	d2_normalize(t_double2 v)
{
	double	m;

	m = sqrt(d2_dot_product(v, v));
	return ((t_double2){.x = v.x * m, .y = v.y * m});
}
