/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:18:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 13:46:49 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

static void		mf_get_ops(t_params *p, char **str)
{
	while (**str == '-' || **str == '+' || **str == '#' ||
	**str == '0' || **str == ' ')
	{
		p->flags ^= (**str == '-' && (p->flags & RPAD) != RPAD) ? RPAD : 0;
		p->flags ^= (**str == '+' && (p->flags & SIGN) != SIGN) ? SIGN : 0;
		p->flags ^= (**str == '#' && (p->flags & ALTERNATE) != ALTERNATE) ?
																ALTERNATE : 0;
		p->flags ^= (**str == '0' && (p->flags & ZPAD) != ZPAD) ? ZPAD : 0;
		p->flags ^= (**str == ' ' && (p->flags & BLANK) != BLANK) ? BLANK : 0;
		(*str)++;
	}
}

static void		mf_get_prec(va_list *ap, t_params *params, char **str)
{
	if (**str == '.')
	{
		(*str)++;
		params->flags ^= PRECISION;
		params->prec = 0;
		if (mf_isdigit(*(*str)) || *(*str) == '*')
		{
			if (**str == '*')
			{
				params->prec = va_arg(*ap, int);
				(*str)++;
			}
			else
			{
				params->prec = mf_atoi(*str);
				while (mf_isdigit(**str))
					(*str)++;
			}
		}
	}
}

static void		mf_get_size(t_params *params, char **str)
{
	params->convert = (**str == 'h') ? h : params->convert;
	params->convert = (**str == 'l') ? l : params->convert;
	params->convert = (**str == 'L') ? L : params->convert;
	if (**str == 'L')
		(*str)++;
	if (**str == 'h' || **str == 'l')
	{
		(*str)++;
		params->convert = (**str == 'h' && params->convert == h)
										? hh : params->convert;
		params->convert = (**str == 'l' && params->convert == l)
										? ll : params->convert;
		*str = (**str == 'h' || **str == 'l') ? (*str + 1) : *str;
	}
}

static	void	mf_get_type(t_params *params, char **str)
{
	char	*tmp;

	tmp = *str;
	params->type = na;
	params->type = (**str == 'c') ? c : params->type;
	params->type = (**str == 's') ? s : params->type;
	params->type = (**str == 'p') ? p : params->type;
	params->type = (**str == 'd') ? d : params->type;
	params->type = (**str == 'i') ? i : params->type;
	params->type = (**str == 'o') ? o : params->type;
	params->type = (**str == 'u') ? u : params->type;
	params->type = (**str == 'U') ? u : params->type;
	params->type = (**str == 'x') ? x : params->type;
	params->type = (**str == 'X') ? X : params->type;
	params->type = (**str == 'f') ? f : params->type;
	params->type = (**str == '%') ? pct : params->type;
	if (params->type == na)
		params->letter = *tmp;
	(*str)++;
}

char			*mf_parse(va_list *ap, char **str, int *argsize)
{
	t_params	params;
	char		*percent;

	mf_init_param(&params);
	if (**str == '%')
	{
		percent = mf_strnew(1);
		*percent = '%';
		(*str)++;
		*argsize = 1;
		return (percent);
	}
	while (mf_isflag(str))
	{
		mf_get_ops(&params, str);
		if (!(params.flags & PRECISION))
			mf_get_width(ap, &params, str);
		mf_get_prec(ap, &params, str);
		mf_get_size(&params, str);
	}
	if (**str == '\0')
		return (NULL);
	mf_get_type(&params, str);
	return (mf_dispatch(ap, &params, argsize));
}
