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

	if (id < 0 || (w = get_world()) == NULL
			|| id >= (int32_t)w->lib.nb_functions)
		return ;
	execute_function(&w->lib.function[id], param, w->effect_statics[id], 1);
}
