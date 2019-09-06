/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 23:42:34 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/30 12:44:56 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var.h"

int		mf_clamp_int(int value, int min, int max)
{
	const int tmp = (value < min) ? min : value;

	return ((tmp > max) ? max : tmp);
}

double	mf_clamp_double(double value, double min, double max)
{
	const double tmp = (value < min) ? min : value;

	return ((tmp > max) ? max : tmp);
}
