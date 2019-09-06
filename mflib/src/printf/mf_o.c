/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_o.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:34:57 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 23:47:31 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

static int		mf_plen(unsigned long long p0)
{
	int i;

	i = 0;
	if (p0 == 0)
		return (1);
	while (p0 > 0)
	{
		i++;
		p0 /= 8;
	}
	return (i);
}

static char		*mf_get_octal(t_params *param, unsigned long long num)
{
	short		len;
	short int	tmp;
	short		count;
	char		*res;

	len = mf_plen(num);
	len = ((param->flags & ALTERNATE) == ALTERNATE && num) ? len + 1 : len;
	len = ((param->flags & PRECISION) == PRECISION &&
	(int)param->prec > len) ? (int)param->prec : len;
	if (!(res = mf_strnew(len)))
		return (NULL);
	count = -1;
	while (++count < len)
		res[count] = '0';
	count = len;
	while (--count >= 0)
	{
		tmp = num % 8;
		num /= 8;
		res[count] = tmp + '0';
	}
	return (res);
}

char			*mf_o_func(va_list *ap, t_params *p)
{
	unsigned long long	num;
	int					len;
	char				*tmpres;
	char				*res;

	num = mf_get_ouxxb(ap, p);
	if (!(tmpres = mf_get_octal(p, num)))
		return (NULL);
	if (!num && (p->flags & PRECISION) && !p->prec && !(p->flags & ALTERNATE))
		*tmpres = '\0';
	num = ((p->flags & WIDTH) == WIDTH && p->width >
	mf_strlen(tmpres)) ? p->width : mf_strlen(tmpres);
	if (!(res = mf_strnew(num)))
		free(tmpres);
	if (!res)
		return (NULL);
	len = num;
	while (num)
		res[--num] = ((p->flags & ZPAD) == ZPAD && (p->flags & RPAD) !=
		RPAD && (p->flags & PRECISION) != PRECISION) ? '0' : ' ';
	mf_strncpy((p->flags & RPAD) == RPAD ? res : res +
	(len - mf_strlen(tmpres)), tmpres, mf_strlen(tmpres));
	free(tmpres);
	p->size = mf_strlen(res);
	return (res);
}
