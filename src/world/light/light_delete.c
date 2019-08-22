/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:33:41 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 16:40:38 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"

int			light_delete(t_light_comp *lcomp, int id)
{
	t_light 	*tmp;
	int			index;

	index = -1;
	while (++index < lcomp->light_count)
		if (lcomp->lights[index].id == id)
			break;
	if (index < 0 || index >= lcomp->light_count || !(lcomp))
		return (0);
	if (!(tmp = (t_light *)malloc(sizeof(t_light) * (lcomp->light_count - 1))))
	{
		lcomp->light_count = 0;
		free(lcomp->lights);
		lcomp->lights = NULL;
		return (0);
	}
	mf_memcpy(tmp, lcomp->lights, index * sizeof(t_light));
	mf_memcpy(&tmp[index], &lcomp->lights[index + 1], sizeof(t_light) * (lcomp->light_count - index - 1));
	free(lcomp->lights);
	lcomp->lights = tmp;
	lcomp->light_count--;
	return (1);
}