/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:51:38 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/06 10:04:09 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"

static unsigned long long	mf_length(unsigned long long n)
{
	int	size;

	if (n == 0)
		return (1);
	size = 0;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char						*mf_uitoa(unsigned long long n)
{
	unsigned long long	nb;
	int					size;
	char				*new;

	nb = n;
	size = mf_length(nb);
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	new[size] = '\0';
	while (--size >= 0)
	{
		new[size] = (nb % 10) + '0';
		nb /= 10;
	}
	return (new);
}
