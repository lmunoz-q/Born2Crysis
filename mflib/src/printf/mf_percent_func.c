/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_percent_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 13:16:57 by kle-van-          #+#    #+#             */
/*   Updated: 2019/09/04 14:00:41 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

char	*mf_percent_func(t_params *param)
{
	char	*res;
	char	*tmp;
	int		pad;

	pad = 0;
	if ((param->flags & WIDTH) == WIDTH)
		pad = (param->width - 1);
	if (!(res = mf_strnew(pad + 1)))
		return (NULL);
	tmp = res;
	if ((param->flags & RPAD) != RPAD && (param->flags & ZPAD) == ZPAD)
		mf_printpad_zeros(&tmp, 0, pad);
	else if ((param->flags & RPAD) != RPAD && (param->flags & ZPAD) != ZPAD)
		mf_printpad_zeros(&tmp, pad, 0);
	*tmp++ = '%';
	if ((param->flags & RPAD) == RPAD)
		mf_printpad_zeros(&tmp, pad, 0);
	param->size = pad + 1;
	return (res);
}
