/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 08:59:00 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/20 09:50:24 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"

double		mf_atof(const char *str)
{
	t_bool		neg;
	double		res;
	long long	div;

	res = 0;
	div = 10;
	neg = FALSE;
	while (mf_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		neg = (*str++ == '-') ? TRUE : FALSE;
	while (*str >= '0' && *str <= '9')
		res = (res * 10) + ((*str++) - '0');
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			res += (double)(*str++ - '0') / (double)div;
			div *= 10;
		}
	}
	return ((neg) ? -res : res);
}
