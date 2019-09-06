/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:23:54 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/15 17:52:06 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmemory.h"

void	*mf_memcpy(void *dst, const void *src, size_t n)
{
	char *d;

	d = dst;
	while (n--)
		*(char *)dst++ = *(char *)src++;
	return (d);
}
