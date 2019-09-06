/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_dui.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:33:16 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 13:53:21 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

void		mf_printpad_zeros(char **tmp, int padsize, int nbz)
{
	while (padsize)
	{
		**tmp = ' ';
		(*tmp)++;
		padsize--;
	}
	while (nbz)
	{
		**tmp = '0';
		(*tmp)++;
		nbz--;
	}
}

static char	*mf_subsub_dui(t_aille *data, int sign, char *nb, t_params *param)
{
	char	*res;
	char	*tmp;
	char	*tmp2;

	if (!(res = mf_strnew(data->padsize + data->nbz + data->size + (sign % 2))))
		return (NULL);
	tmp = res;
	tmp2 = nb;
	if (!((param->flags & RPAD) == RPAD) && data->padsize)
		mf_printpad_zeros(&tmp, data->padsize, 0);
	if (sign == 1)
		*tmp++ = ' ';
	else if (sign == 3)
		*tmp++ = '+';
	else if (*nb == '-')
		*tmp++ = *nb++;
	if (data->nbz)
		mf_printpad_zeros(&tmp, 0, data->nbz);
	while (*nb)
		*tmp++ = *nb++;
	if ((param->flags & RPAD) == RPAD && data->padsize)
		mf_printpad_zeros(&tmp, data->padsize, 0);
	param->size = mf_strlen(res);
	free(tmp2);
	return (res);
}

static char	*mf_sub_dui(t_params *p, long long nb, int sign)
{
	char	*nbstr;
	t_aille	d;

	if (!(nbstr = mf_itoa(nb)))
		return (NULL);
	d.size = mf_strlen(nbstr);
	d.nbz = 0;
	d.padsize = 0;
	if (p->flags & PRECISION)
		d.nbz = ((int)p->prec > d.size) ? (p->prec - d.size) : 0;
	if (p->flags & PRECISION)
		d.nbz += (nb < 0) ? 1 : 0;
	else if ((p->flags & ZPAD) == ZPAD && (p->flags & RPAD) != RPAD)
	{
		d.nbz = ((p->flags & WIDTH) && (int)p->width >
	(d.size + (sign % 2))) ? (p->width - (d.size + (sign % 2))) : 0;
		return (mf_subsub_dui(&d, sign, nbstr, p));
	}
	d.padsize = ((p->flags & WIDTH) && (int)p->width > (d.size +
		(sign % 2) + d.nbz)) ? (p->width - (d.size + (sign % 2) + d.nbz)) : 0;
	if ((p->flags & PRECISION) && p->prec == 0 && nb == 0)
		d.padsize += (d.padsize == 0) ? 0 : 1;
	if ((p->flags & PRECISION) && p->prec == 0 && nb == 0)
		*nbstr = 0;
	return (mf_subsub_dui(&d, sign, nbstr, p));
}

static char	*mf_sub_dui2(t_params *param, unsigned long long nb)
{
	char	*nbstr;
	t_aille	data;

	if (!(nbstr = mf_uitoa(nb)))
		return (NULL);
	data.size = mf_strlen(nbstr);
	data.nbz = 0;
	data.padsize = 0;
	if ((param->flags & PRECISION) == PRECISION)
		data.nbz = ((int)param->prec > data.size) ?
											(param->prec - data.size) : 0;
	else if ((param->flags & ZPAD) == ZPAD && (param->flags & RPAD) != RPAD)
	{
		data.nbz = ((param->flags & WIDTH) == WIDTH && (int)param->width >
		(data.size + data.nbz)) ? (param->width - (data.size + data.nbz)) : 0;
		return (mf_subsub_dui(&data, 0, nbstr, param));
	}
	data.padsize = ((param->flags & WIDTH) == WIDTH && (int)param->width >
		(data.size + data.nbz)) ? (param->width - (data.size + data.nbz)) : 0;
	if ((param->flags & PRECISION) && param->prec == 0 && nb == 0)
		data.padsize += (data.padsize == 0) ? 0 : 1;
	if ((param->flags & PRECISION) && param->prec == 0 && nb == 0)
		*nbstr = 0;
	return (mf_subsub_dui(&data, 0, nbstr, param));
}

char		*mf_dui_func(va_list *ap, t_params *param)
{
	int					sign;
	long long			nb;
	unsigned long long	nb2;

	sign = 0;
	nb = 0;
	if (param->type == i || param->type == d)
	{
		nb = mf_get_di(ap, param);
		if ((param->flags & BLANK) == BLANK)
			sign = 1;
		if ((param->flags & SIGN) == SIGN)
			sign = 3;
		sign = (nb < 0) ? 0 : sign;
		return (mf_sub_dui(param, nb, sign));
	}
	else
		nb2 = mf_get_ouxxb(ap, param);
	return (mf_sub_dui2(param, nb2));
}
