/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:39:29 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/15 17:35:24 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"

char	*mf_strcpy(char *dst, const char *src)
{
	char *temp;

	temp = dst;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (temp);
}
