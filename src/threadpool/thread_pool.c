/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:29:34 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/14 12:34:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_thread_pool	*set_thread_pool(int slaves, int max_work)
{
	static t_thread_pool	*pool = NULL;

	if (!pool)
		pool = thread_pool_init(slaves, max_work);
	return (pool);
}

t_thread_pool	*get_thread_pool()
{
	return (set_thread_pool(0, 0));
}
