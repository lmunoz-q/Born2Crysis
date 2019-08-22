/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 13:53:12 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 14:00:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"

void		light_add(t_light_comp *comp, t_light light)
{
	t_light *tmp;
	
	if (!(tmp = (t_light *)malloc(sizeof(t_light) * (comp->light_count + 1))))
		return ;
	mf_memcpy(tmp, comp->lights, sizeof(t_light) * comp->light_count);
	tmp[comp->light_count] = light;
	if (comp->lights)
		free(comp->lights);
	comp->lights = tmp;
	comp->light_count++;
}