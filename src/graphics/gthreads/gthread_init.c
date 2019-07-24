/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gthread_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:12:26 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/25 00:10:22 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void			gthreads_workers_init(t_gthreads *gt, SDL_Surface *s)
{
	int		i;
	double	*z;

	z = get_zbuff();
	i = -1;
	while (++i < gt->worker_count)
	{
		gt->workers[i].id = i;
		gt->workers[i].parent = gt;
		gt->workers[i].start = gt->delta * i;
		gt->workers[i].end = gt->delta * (i + 1);
		gt->workers[i].pixels = &((uint32_t *)s->pixels)[gt->workers[i].start * s->w];
		gt->workers[i].zbuff = &z[gt->workers[i].start * s->w];
		pthread_create(&gt->workers[i].thread, NULL, gthread_work, &gt->workers[i]);
	}
}

t_gthreads			*gthread_init(int	workers, SDL_Surface *s, t_polygon *p)
{
	static t_gthreads	*gt = NULL;

	if (!gt)
	{
		if (!(gt = (t_gthreads *)malloc(sizeof(t_gthreads))))
			return (NULL);
		if (!(gt->workers = (t_gworker *)malloc(sizeof(t_gworker) * workers)))
		{
			free(gt);
			return (NULL);
		}
		gt->delta = (double)s->h / (double)workers;
		gt->wait = FALSE;
		gt->work = FALSE;
		gt->worker_count = workers;
		gt->plist = p;
		gt->polygon_count = 0;
		gt->active = workers;
		pthread_cond_init(&gt->wait_cnd, NULL);
		pthread_cond_init(&gt->work_cnd, NULL);
		pthread_mutex_init(&gt->wait_mtx, NULL);
		pthread_mutex_init(&gt->work_mtx, NULL);
		gthreads_workers_init(gt, s);
	}
	return (gt);
}

t_gthreads			*gthread_get()
{
	return (gthread_init(-1, NULL, NULL));
}