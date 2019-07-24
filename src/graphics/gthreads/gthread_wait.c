/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gthread_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:10:58 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/25 00:01:49 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void				gthread_wait(t_gthreads *gt)
{
	pthread_mutex_lock(&gt->wait_mtx);
	while (gt->wait)
		pthread_cond_wait(&gt->wait_cnd, &gt->wait_mtx);
	pthread_mutex_unlock(&gt->wait_mtx);
}