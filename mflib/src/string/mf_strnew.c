/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:30:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/15 17:43:00 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"
#include "mfmemory.h"

char	*mf_strnew(size_t size)
{
	char *res;

	if (!(res = (char *)malloc(sizeof(size_t) * (size + 1))))
		return (NULL);
	mf_bzero(res, size + 1);
	return (res);
}
