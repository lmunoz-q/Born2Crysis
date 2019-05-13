/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:56:57 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/13 20:29:17 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_test(void *param)
{
	t_e *e = param;

	e->camera.pos[0] += 0.1;
}

void	kf_test2(void *param)
{
	t_e *e = param;

	e->camera.pos[0] -= 0.1;
}
