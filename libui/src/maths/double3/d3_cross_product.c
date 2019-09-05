/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d3_cross_product.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:29:25 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:29:26 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_maths.h>

t_double3	d3_cross_product(t_double3 a, t_double3 b)
{
	return ((t_double3){.x = a.y * b.z - a.z * b.y, .y = a.z * b.x - a.x * b.z,
					.z = a.x * b.y - a.y * b.x});
}
