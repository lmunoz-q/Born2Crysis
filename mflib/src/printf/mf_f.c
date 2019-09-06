/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_f.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:35:09 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 14:01:42 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

static int			mf_nbrlen(long double n)
{
	int			i;
	long long	tmp;

	tmp = mf_floor(n);
	i = (tmp < 1) ? 1 : 0;
	while (tmp >= 1)
	{
		tmp /= 10;
		i++;
	}
	return (i);
}

static long double	mf_get_frac(long double num, int prec)
{
	long double tmp;

	tmp = num;
	while (prec--)
		tmp *= 10.L;
	if (mf_fmod((tmp * 10.L), 10) >= 5)
	{
		tmp *= 10.L;
		tmp += 10.L - mf_fmod(tmp, 10);
		tmp /= 10.L;
	}
	return (tmp);
}

static char			*mf_ftoa(long double num, t_params *p)
{
	int			len;
	int			i;
	long double	tmp;
	char		*res;

	num = (num < 0) ? -num : num;
	tmp = num;
	len = mf_nbrlen(num) + p->prec +
	((p->prec > 0 || p->flags & ALTERNATE) ? 1 : 0);
	if (!(res = mf_strnew(len)))
		return (NULL);
	i = mf_nbrlen(num);
	if (!(tmp < 1.L))
		tmp = (!p->prec && (num) >= 0.5L) ? tmp + 1.L : tmp;
	mf_div_f(&i, &tmp, res);
	i = mf_nbrlen(num);
	if (p->prec > 0 || p->flags & ALTERNATE)
		res[i++] = '.';
	num = mf_get_frac(num, p->prec);
	while (len > i)
	{
		res[--len] = (mf_fmod(num, 10.L) + '0');
		num /= 10;
	}
	return (res);
}

static void			mf_writefloat(t_params *p, t_aille *len,
									char *res, char *nb)
{
	char *fnb;

	fnb = nb;
	if (!(p->flags & RPAD) && !(p->flags & ZPAD))
		mf_printpad_zeros(&res, len->padsize, 0);
	if (len->sign == 1)
		*res++ = ' ';
	else if (len->sign == 3)
		*res++ = '+';
	else if (len->sign == 5)
		*res++ = '-';
	if (!(p->flags & RPAD) && (p->flags & ZPAD))
		mf_printpad_zeros(&res, 0, len->nbz);
	while (*nb)
		*res++ = *nb++;
	if (p->flags & RPAD)
		mf_printpad_zeros(&res, len->padsize, 0);
	free(fnb);
}

char				*mf_f_func(va_list *ap, t_params *p)
{
	char		*snum;
	long double	num;
	t_aille		len;
	char		*res;

	len.nbz = 0;
	len.padsize = 0;
	p->prec = (p->flags & PRECISION) ? p->prec : 6;
	num = mf_get_float(ap, p);
	if (!(snum = mf_ftoa(num, p)))
		return (NULL);
	mf_init_len(&len, p, snum, num);
	if (!(p->flags & RPAD) && (p->flags & ZPAD))
		len.nbz = ((p->flags & WIDTH) && (int)p->width >
	(len.size + (len.sign % 2))) ? (p->width - len.size - (len.sign % 2)) : 0;
	else
		len.padsize = ((p->flags & WIDTH) && (int)p->width >
	(len.size + (len.sign % 2))) ? (p->width - len.size - (len.sign % 2)) : 0;
	if (!(res = mf_strnew((len.sign % 2) + len.size + len.nbz + len.padsize)))
		free(snum);
	if (!res)
		return (NULL);
	mf_writefloat(p, &len, res, snum);
	p->size = mf_strlen(res);
	return (res);
}
