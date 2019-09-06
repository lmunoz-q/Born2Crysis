/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d2_scale.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:29:01 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:29:02 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_maths.h>

t_double2	d2_scale(t_double2 v, double scalar)
{
	return ((t_double2){.x = v.x * scalar, .y = v.y * scalar});
}
