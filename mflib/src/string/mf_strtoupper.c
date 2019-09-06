/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:56:26 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/06 10:04:16 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstring.h"

void	mf_strtoupper(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		*str = mf_toupper(*str);
		str++;
	}
}
