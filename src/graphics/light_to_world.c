/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_to_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 09:35:30 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 19:04:19 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		light_to_world(t_light_comp *comp)
{
	int i;

	if (!comp)
		return ;
	i = -1;
	while (++i < comp->light_count)
	{
		comp->lights[i].pos = mat4vec4_multiply(comp->lights[i].mat, comp->lights[i].pos_o);
	}
}
