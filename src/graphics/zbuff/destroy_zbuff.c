/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_zbuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:33:36 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/01 17:41:01 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		destroy_zbuff(void)
{
	double *zbuff;

	if (!(zbuff = get_zbuff()))
		return ;
	free(zbuff);
}
