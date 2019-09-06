/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:49:37 by kle-van-          #+#    #+#             */
/*   Updated: 2019/09/04 14:00:29 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

long long			mf_get_di(va_list *ap, t_params *param)
{
	if (param->convert == none)
		return (va_arg(*ap, int));
	else if (param->convert == hh)
		return ((char)va_arg(*ap, int));
	else if (param->convert == h)
		return ((short)va_arg(*ap, int));
	else if (param->convert == l)
		return (va_arg(*ap, long));
	else if (param->convert == ll)
		return (va_arg(*ap, long long));
	else
		return (va_arg(*ap, long));
	return (0);
}

unsigned long long	mf_get_ouxxb(va_list *ap, t_params *param)
{
	if (param->convert == none)
		return (va_arg(*ap, unsigned int));
	else if (param->convert == hh)
		return ((unsigned char)va_arg(*ap, unsigned int));
	else if (param->convert == h)
		return ((unsigned short)va_arg(*ap, unsigned int));
	else if (param->convert == l)
		return (va_arg(*ap, unsigned long));
	else if (param->convert == ll)
		return (va_arg(*ap, unsigned long long));
	else
		return (va_arg(*ap, unsigned long));
	return (0);
}

long double			mf_get_float(va_list *ap, t_params *param)
{
	if (param->convert == none)
		return ((long double)va_arg(*ap, double));
	else if (param->convert == l)
		return ((long double)va_arg(*ap, double));
	else if (param->convert == L)
		return ((long double)va_arg(*ap, long double));
	return (0.0);
}
