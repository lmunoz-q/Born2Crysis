/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2019/09/03 17:39:37 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>

void	apply_effect(int32_t id, void *param)
{
	t_world		*w;
	t_effect	*effect;

	if (id < 0 || (w = get_world()) == NULL || id >= w->nb_effects)
		return ;
	effect = &w->effects[id];
	execute_function(&effect->func, param, effect->ptr, 0);
}
