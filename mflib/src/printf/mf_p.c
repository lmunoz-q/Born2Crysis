/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:34:38 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 23:46:11 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

static int	mf_plen(long long p0)
{
	int i;

	i = 0;
	if (p0 == 0)
		return (1);
	while (p0 > 0)
	{
		i++;
		p0 /= 16;
	}
	return (i);
}

static char	*mf_get_address(long long address, t_params *param)
{
	char	*res;
	int		i;
	char	c;

	i = ((param->flags & PRECISION) == PRECISION
	&& (int)param->prec > mf_plen(address)) ?
						(int)param->prec + 2 : mf_plen(address) + 2;
	i = ((param->flags & PRECISION) != PRECISION
	&& (param->flags & WIDTH) == WIDTH
	&& (param->flags & ZPAD) == ZPAD
	&& (param->flags & RPAD) != RPAD
	&& (int)param->width > i) ? (int)param->width : i;
	if (!(res = mf_strnew(i)))
		return (NULL);
	if (address == 0)
		res[0] = '0';
	while (address != 0)
	{
		c = address % 16;
		address /= 16;
		res[--i] = (c < 10) ? c + '0' : c - 10 + 'a';
	}
	while (--i != -1)
		res[i] = (i == 1) ? 'x' : '0';
	return (res);
}

char		*mf_p_func(va_list *ap, t_params *param)
{
	long long	p0;
	char		*addr;
	char		*res;
	int			len;
	int			i;

	p0 = (long long)va_arg(*ap, void*);
	if (!(addr = mf_get_address(p0, param)))
		return (NULL);
	len = ((param->flags & WIDTH) == WIDTH) && param->width >
			mf_strlen(addr) ? param->width : mf_strlen(addr);
	if (!(res = mf_strnew(len)))
	{
		free(addr);
		return (NULL);
	}
	i = -1;
	while (++i < len)
		res[i] = ' ';
	mf_strncpy(((param->flags & RPAD) == RPAD) ? res : res +
			(len - mf_strlen(addr)), addr, mf_strlen(addr));
	free(addr);
	param->size = mf_strlen(res);
	return (res);
}
