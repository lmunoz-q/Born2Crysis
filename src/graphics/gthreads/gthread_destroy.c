/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gthread_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 15:11:42 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/01 18:43:06 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	gthread_stop_threads(t_gthreads *gt)
{
	int i;

	gt->alive = FALSE;
	gthread_launch(gt);
	i = -1;
	while (++i < gt->worker_count)
		pthread_join(gt->workers[i].thread, NULL);
}

void		gthread_destroy(t_gthreads *gt)
{
	if (!gt->worker_count || gt->alive == FALSE)
		return ;
	gthread_stop_threads(gt);
	free(gt->workers);
	pthread_mutex_destroy(&gt->wait_mtx);
	pthread_mutex_destroy(&gt->work_mtx);
	pthread_cond_destroy(&gt->wait_cnd);
	pthread_cond_destroy(&gt->work_cnd);
}
