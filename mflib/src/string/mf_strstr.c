/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:54:54 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 14:59:45 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"

char	*mf_strstr(const char *haystack, const char *needle)
{
	char *htemp;
	char *ntemp;

	htemp = NULL;
	ntemp = NULL;
	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		htemp = (char *)haystack;
		ntemp = (char *)needle;
		while (*haystack++ == *needle++)
		{
			if (*needle == '\0')
				return (htemp);
		}
		if (htemp != haystack)
		{
			haystack = htemp;
			needle = ntemp;
		}
		haystack++;
	}
	return (NULL);
}
