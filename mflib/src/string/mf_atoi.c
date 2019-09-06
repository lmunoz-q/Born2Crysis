/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 22:51:55 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/19 23:00:19 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"

int			mf_atoi(const char *str)
{
	long long	neg;
	long long	sum;

	sum = 0;
	neg = 1;
	while (mf_isspace(*str))
		str++;
	if (*str == 43 || *str == 45)
		neg = (*str++ == 45) ? -1 : 1;
	while (*str < 58 && *str > 47)
		sum = (sum * 10) + ((*str++) - 48);
	return (neg * sum);
}
