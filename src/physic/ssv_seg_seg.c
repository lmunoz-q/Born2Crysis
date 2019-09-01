/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssv_seg_seg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2000/00/00 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <physic.h>

static inline void	i_1(double dbl[9])
{
	if (dbl[8] < 0.0 && !(dbl[8] = 0.0))
	{
		if (dbl[3] < 0.0)
			dbl[7] = 0.0;
		else if (dbl[3] > dbl[0])
			dbl[7] = dbl[5];
		else
		{
			dbl[7] = dbl[3];
			dbl[5] = dbl[0];
		}
	}
	else if (dbl[8] > dbl[6])
	{
		dbl[8] = dbl[6];
		if ((dbl[3] + dbl[1]) < 0.0)
			dbl[7] = 0.0;
		else if ((dbl[3] + dbl[1]) > dbl[0])
			dbl[7] = dbl[5];
		else
		{
			dbl[7] = dbl[3] + dbl[1];
			dbl[5] = dbl[0];
		}
	}
}

static inline void	i_0(double dbl[9])
{
	if (dbl[5] < 1.19209290E-07)
	{
		dbl[7] = 0.0;
		dbl[5] = 1.0;
		dbl[8] = dbl[4];
		dbl[6] = dbl[2];
	}
	else
	{
		dbl[7] = (dbl[1] * dbl[4] - dbl[2] * -dbl[3]);
		dbl[8] = (dbl[0] * dbl[4] - dbl[1] * -dbl[3]);
		if (dbl[7] < 0.0)
		{
			dbl[7] = 0.0;
			dbl[8] = dbl[4];
			dbl[6] = dbl[2];
		}
		else if (dbl[7] > dbl[5])
		{
			dbl[7] = dbl[5];
			dbl[8] = dbl[4] + dbl[1];
			dbl[6] = dbl[2];
		}
	}
	i_1(dbl);
}

/*
** shortest separating vector between two segments ab and cd (might be the nul
** vector if collinear segments touching)
*/

inline t_vec3d		ssv_seg_seg(t_vec3d s1a, t_vec3d s1b,
								t_vec3d s2a, t_vec3d s2b)
{
	t_vec3d	u;
	t_vec3d	v;
	t_vec3d	w;
	double	dbl[9];

	u = vec3vec3_substract(s1b, s1a);
	v = vec3vec3_substract(s2b, s2a);
	w = vec3vec3_substract(s1a, s2a);
	dbl[0] = vec3_dot(u, u);
	dbl[1] = vec3_dot(u, v);
	dbl[2] = vec3_dot(v, v);
	dbl[3] = -vec3_dot(u, w);
	dbl[4] = vec3_dot(v, w);
	dbl[5] = dbl[0] * dbl[2] - dbl[1] * dbl[1];
	dbl[6] = dbl[5];
	i_0(dbl);
	return (vec3vec3_add(w, vec3vec3_substract(vec3scalar_multiply(u,
		fabs(dbl[7]) < 1.19209290E-07 ? 0.0 : dbl[7] / dbl[5]),
		vec3scalar_multiply(v, fabs(dbl[8]) < 1.19209290E-07 ? 0.0
		: dbl[8] / dbl[6]))));
}
