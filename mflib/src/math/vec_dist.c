/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_dist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 20:09:13 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/13 20:14:50 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

double			vec3vec3_dist(t_vec3d v1, t_vec3d v2)
{
	double res;

	res = ((v2.n.x - v1.n.x) * (v2.n.x - v1.n.x));
	res += ((v2.n.y - v1.n.y) * (v2.n.y - v1.n.y));
	res += ((v2.n.z - v1.n.z) * (v2.n.z - v1.n.z));
	return (sqrt(res));
}

double			vec2vec2_dist(t_vec2d v1, t_vec2d v2)
{
	double res;

	res = ((v2.n.x - v1.n.x) * (v2.n.x - v1.n.x));
	res += ((v2.n.y - v1.n.y) * (v2.n.y - v1.n.y));
	return (sqrt(res));
}
