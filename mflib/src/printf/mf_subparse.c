/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_subparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:56:32 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 14:00:52 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

int		mf_isflag(char **str)
{
	if (mf_isdigit(**str) || **str == '*')
		return (1);
	else if (**str == ' ' || **str == '-' || **str == '+' || **str == '#' ||
																**str == '0')
		return (1);
	else if (**str == '.')
		return (1);
	else if (**str == 'h' || **str == 'l' || **str == 'L')
		return (1);
	return (0);
}

void	mf_get_width(va_list *ap, t_params *params, char **str)
{
	if (mf_isdigit(**str) || **str == '*')
		params->flags ^= WIDTH;
	if (mf_isdigit(**str))
		params->width = mf_atoi(*str);
	else if (**str == '*')
		params->width = va_arg(*ap, int);
	while (mf_isdigit(**str) || **str == '*')
		(*str)++;
}

void	mf_init_param(t_params *params)
{
	params->flags = 0;
	params->convert = 0;
	params->prec = 0;
	params->width = 0;
}

void	mf_init_len(t_aille *len, t_params *p, char *nb, long double num)
{
	len->size = mf_strlen(nb);
	len->sign = (p->flags & BLANK) ? 1 : 0;
	len->sign = (p->flags & SIGN) ? 3 : len->sign;
	len->sign = (num < 0) ? 5 : len->sign;
}

void	mf_div_f(int *i, long double *tmp, char *res)
{
	while (--(*i) >= 0)
	{
		res[*i] = mf_fmod(*tmp, 10) + '0';
		*tmp /= 10;
	}
}
