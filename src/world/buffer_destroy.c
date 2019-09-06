/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:39:38 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/01 17:40:58 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	buffer_destroy(void)
{
	t_polygon *p;

	if (!(p = get_polygon_buffer()))
		return ;
	free(p);
}
