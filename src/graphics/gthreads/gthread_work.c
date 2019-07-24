/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gthread_work.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 22:05:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/25 00:01:39 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static	void		wake_up_main_thread(t_gthreads *gt)
{
	
	if (gt->active == 0)
	{
		pthread_mutex_lock(&gt->wait_mtx);
		gt->wait = FALSE;
		pthread_cond_broadcast(&gt->wait_cnd);
		pthread_mutex_unlock(&gt->wait_mtx);
	}
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
		wake_up_main_thread(gt);
		while (!gt->work)
			pthread_cond_wait(&gt->work_cnd, &gt->work_mtx);
		gt->work = FALSE;
		gt->active++;
		pthread_mutex_unlock(&gt->work_mtx);
		gthread_raster(gt, worker);
	}
}
