/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:59:25 by kle-van-          #+#    #+#             */
/*   Updated: 2019/09/04 13:55:21 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

static void	mf_pad(t_params *param, char **tmp)
{
	while (param->width-- > 1)
	{
		if (!((param->flags & RPAD) == RPAD))
		{
			**tmp = (((param->flags & ZPAD) == ZPAD) ? '0' : ' ');
			(*tmp)++;
			param->size++;
		}
		else
		{
			(*tmp)++;
			**tmp = ' ';
			param->size++;
		}
	}
}

char		*mf_c_func(va_list *ap, t_params *param)
{
	char	*str;
	char	*tmp;
	char	c;

	param->size = 0;
	str = mf_strnew(((param->flags & WIDTH) == WIDTH) ? param->width : 1);
	if (!str)
		return (NULL);
	tmp = str;
	if (((param->flags & WIDTH) == WIDTH) && (param->width > 1) &&
											!((param->flags & RPAD) == RPAD))
		mf_pad(param, &tmp);
	c = (char)va_arg(*ap, int);
	*tmp = c;
	param->size++;
	if (((param->flags & WIDTH) == WIDTH) && (param->width > 1) &&
											((param->flags & RPAD) == RPAD))
		mf_pad(param, &tmp);
	return (str);
}
