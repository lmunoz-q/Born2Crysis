/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d2_cross_product.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:28:48 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:28:48 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_maths.h>

double		d2_cross_product(t_double2 a, t_double2 b)
{
	return (a.y * b.x - a.x * b.y);
}

double		d2_cross_product_flat(double ax, double ay, double bx, double by)
{
	return (ay * bx - ax * by);
}
