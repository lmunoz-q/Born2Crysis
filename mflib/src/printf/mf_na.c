/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_na.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:08:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 14:00:18 by mfischer         ###   ########.fr       */
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

char		*mf_na_func(t_params *param)
{
	char	*str;
	char	*tmp;

	param->size = 0;
	if (!(str = mf_strnew(((param->flags & WIDTH) == WIDTH) ?
											param->width : 1)))
		return (NULL);
	tmp = str;
	if (((param->flags & WIDTH) == WIDTH) && (param->width > 1) &&
											!((param->flags & RPAD) == RPAD))
		mf_pad(param, &tmp);
	*tmp = param->letter;
	param->size++;
	if (((param->flags & WIDTH) == WIDTH) && (param->width > 1) &&
											((param->flags & RPAD) == RPAD))
		mf_pad(param, &tmp);
	return (str);
}
