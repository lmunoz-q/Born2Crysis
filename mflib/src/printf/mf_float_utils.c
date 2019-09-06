/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_float_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:59:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 14:01:07 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfprintf.h"

long long	mf_fmod(long double num, int mod)
{
	return (num - (mod * (mf_floor((num / mod)))));
}

long long	mf_floor(long double numb)
{
	long long nb;

	nb = (long long)numb;
	return ((numb < nb) ? nb - 1 : nb);
}
