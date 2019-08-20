/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_to_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:33:19 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/16 16:33:22 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <physic.h>
#include <world.h>

t_wall	polygon_to_wall(t_polygon poly)
{
	t_vec3d	triangle[3];

	triangle[0] = (t_vec3d){.a = {poly.v01.a[0], poly.v01.a[1], poly.v01.a[2]}};
	triangle[1] = (t_vec3d){.a = {poly.v12.a[0], poly.v12.a[1], poly.v12.a[2]}};
	triangle[2] = (t_vec3d){.a = {poly.v20.a[0], poly.v20.a[1], poly.v20.a[2]}};
	return (wall_from_triangle(triangle));
}
