/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 08:53:51 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/20 08:54:12 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"

char	*mf_strsub(char const *s, unsigned int start, size_t len)
{
	char	*res;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = start;
	j = 0;
	while (j < (int)len)
		res[j++] = s[i++];
	res[len] = '\0';
	return (res);
}
