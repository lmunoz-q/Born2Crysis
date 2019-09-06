/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 23:47:31 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/24 00:35:49 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var.h"

int			mf_min_int(int num, ...)
{
	va_list	vlist;
	int		res;
	int		tmp;
	int		i;

	va_start(vlist, num);
	res = va_arg(vlist, int);
	i = -1;
	while (++i < num - 1)
		if ((tmp = va_arg(vlist, int)) < res)
			res = tmp;
	va_end(vlist);
	return (res);
}

double		mf_min_double(int num, ...)
{
	va_list	vlist;
	int		res;
	int		tmp;
	int		i;

	va_start(vlist, num);
	res = va_arg(vlist, double);
	i = -1;
	while (++i < num - 1)
		if ((tmp = va_arg(vlist, double)) < res)
			res = tmp;
	va_end(vlist);
	return (res);
}
