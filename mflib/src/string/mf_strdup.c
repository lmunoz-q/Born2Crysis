/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:18:39 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/15 17:42:47 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"

char	*mf_strdup(const char *s1)
{
	char	*res;
	int		size;
	int		x;

	x = -1;
	size = mf_strlen(s1) + 1;
	if (!(res = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	while (++x < (size))
		res[x] = s1[x];
	return (res);
}
