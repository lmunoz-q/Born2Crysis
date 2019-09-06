/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:51:12 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/13 19:53:06 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handler.h"

t_key		gen_key(void (*func)(void *), void *param, t_bool continuous)
{
	t_key	key;

	key.continuous = continuous;
	key.params = param;
	key.func = func;
	key.toggle = TRUE;
	key.active = FALSE;
	return (key);
}
