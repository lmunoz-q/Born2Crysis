/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:41:37 by kle-van-          #+#    #+#             */
/*   Updated: 2019/09/04 13:49:46 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

static char	*mf_dispatch3(t_params *params, int *size, char **str)
{
	if (params->type == pct)
	{
		*str = (mf_percent_func(params));
		*size = params->size;
		return (*str);
	}
	*str = (mf_na_func(params));
	*size = params->size;
	return (*str);
}

static char	*mf_dispatch2(va_list *ap, t_params *params, int *size, char **str)
{
	if (params->type == o)
	{
		*str = (mf_o_func(ap, params));
		*size = params->size;
		return (*str);
	}
	else if (params->type == x || params->type == X)
	{
		*str = (mf_x_func(ap, params));
		*size = params->size;
		return (*str);
	}
	else if (params->type == f)
	{
		*str = (mf_f_func(ap, params));
		*size = params->size;
		return (*str);
	}
	else if (params->type == d || params->type == i || params->type == u)
	{
		*str = (mf_dui_func(ap, params));
		*size = params->size;
		return (*str);
	}
	return (mf_dispatch3(params, size, str));
}

char		*mf_dispatch(va_list *ap, t_params *params, int *argsize)
{
	char *str;

	if (params->type == c)
	{
		str = (mf_c_func(ap, params));
		*argsize = params->size;
		return (str);
	}
	else if (params->type == s)
	{
		str = (mf_s_func(ap, params));
		*argsize = params->size;
		return (str);
	}
	else if (params->type == p)
	{
		str = (mf_p_func(ap, params));
		*argsize = params->size;
		return (str);
	}
	return (mf_dispatch2(ap, params, argsize, &str));
}
