/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:42:34 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 13:42:52 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"

char	*mf_strncpy(char *dst, const char *src, size_t n)
{
	char	*temp;

	temp = dst;
	while (n > 0)
	{
		if (*src != '\0')
			*temp++ = *src++;
		else
			*temp++ = '\0';
		n--;
	}
	return (dst);
}
