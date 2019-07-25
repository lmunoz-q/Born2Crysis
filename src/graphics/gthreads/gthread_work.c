/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gthread_work.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 22:05:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/25 12:48:30 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static	void		wake_up_main_thread(t_gthreads *gt)
{
	pthread_mutex_lock(&gt->wait_mtx);
	if (gt->work_load == 0)
	{
		gt->wait = FALSE;
		pthread_cond_broadcast(&gt->wait_cnd);
	}
	pthread_mutex_unlock(&gt->wait_mtx);
}

void				*gthread_work(void *p)
{
	t_gworker	*worker;
	t_gthreads	*gt;

	worker = p;
	gt = worker->parent;
	while (TRUE)
	{
		pthread_mutex_lock(&gt->work_mtx);
		gt->active--;
		gt->work_load--;
		wake_up_main_thread(gt);
		while (!worker->pending)
			pthread_cond_wait(&gt->work_cnd, &gt->work_mtx);
		gt->active++;
		worker->pending = FALSE;
		pthread_mutex_unlock(&gt->work_mtx);
		gthread_raster(gt, worker);
	}
}
