/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:09:22 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/15 17:44:11 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"

char	*mf_strjoin(char const *s1, char const *s2)
{
	size_t	totlen;
	char	*res;
	size_t	counter;

	if (!s1 || !s2)
		return (NULL);
	totlen = mf_strlen(s1) + mf_strlen(s2);
	if (!(res = (char *)malloc(sizeof(char) * (totlen + 1))))
		return (NULL);
	counter = 0;
	while (*s1)
		res[counter++] = *s1++;
	while (*s2)
		res[counter++] = *s2++;
	res[counter] = '\0';
	return (res);
}
