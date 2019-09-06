/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:31:22 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/13 14:53:34 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"

static int	count_digits(int num)
{
	int i;

	i = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char		*mf_itoa(int num)
{
	char	*res;
	int		len;
	int		neg;

	len = count_digits(num);
	neg = (num < 0) ? 1 : 0;
	len += (num < 0) ? 1 : 0;
	res = (char *)malloc(sizeof(char) * (len + 1));
	res[len] = '\0';
	while (--len >= 0)
	{
		res[len] = (num % 10) + '0';
		num /= 10;
	}
	if (neg)
		res[0] = '-';
	return (res);
}
