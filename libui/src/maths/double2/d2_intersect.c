/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d2_intersect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:28:54 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:28:54 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_maths.h>

t_double2	d2_intersect(t_double2 l1_start, t_double2 l1_end,
						t_double2 l2_start, t_double2 l2_end)
{
	double		l1c;
	double		l2c;
	t_double2	l1d;
	t_double2	l2d;
	double		cd;

	l1c = d2_cross_product(l1_start, l1_end);
	l2c = d2_cross_product(l2_start, l2_end);
	l1d = (t_double2){l1_end.x - l1_start.x, l1_end.y - l1_start.y};
	l2d = (t_double2){l2_end.x - l2_start.x, l2_end.y - l2_start.y};
	cd = d2_cross_product(l1d, l2d);
	return ((t_double2){.x = d2_cross_product_flat(l1c, l1d.x, l2c, l2d.x) / cd,
					.y = d2_cross_product_flat(l1c, l1d.y, l2c, l2d.y) / cd});
}
