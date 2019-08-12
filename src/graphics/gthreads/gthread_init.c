/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gthread_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:12:26 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/12 21:59:13 by mfischer         ###   ########.fr       */
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
		gt->workers[i].start = gt->delta * (double)i;
		gt->workers[i].end = gt->delta * (double)(i + 1);
		gt->workers[i].pixels = &((uint32_t *)s->pixels)[gt->workers[i].start * s->w];
		gt->workers[i].zbuff = &z[gt->workers[i].start * s->w];
		gt->workers[i].pending = FALSE;
		pthread_create(&gt->workers[i].thread, NULL, gthread_work, &gt->workers[i]);
	}
}

t_gthreads			*gthread_init(short	workers, SDL_Surface *s, t_polygon *p, t_gthread_type type)
{
	static t_gthreads	*gt[3] = {NULL, NULL, NULL};

	if (workers < 1000 && workers > 0)
	{
		printf("%d\n", workers);
		if (!(gt[type] = (t_gthreads *)malloc(sizeof(t_gthreads))))
			return (NULL);
		if (!(gt[type]->workers = (t_gworker *)malloc(sizeof(t_gworker) * workers)))//sizeof(t_gworker) * workers)))
		{
			free(gt[type]);
			return (NULL);
		}
		gt[type]->delta = (double)s->h / (double)workers;
		gt[type]->wait = FALSE;
		gt[type]->work = FALSE;
		gt[type]->worker_count = workers;
		gt[type]->plist = p;
		gt[type]->h = s->h;
		gt[type]->w = s->w;
		gt[type]->alive = TRUE;
		gt[type]->polygon_count = 0;
		gt[type]->active = workers;
		pthread_cond_init(&gt[type]->wait_cnd, NULL);
		pthread_cond_init(&gt[type]->work_cnd, NULL);
		pthread_mutex_init(&gt[type]->wait_mtx, NULL);
		pthread_mutex_init(&gt[type]->work_mtx, NULL);
		gthreads_workers_init(gt[type], s);
	}
	return (gt[type]);
}

t_gthreads			*gthread_get(t_gthread_type type)
{
	static	t_gthreads *last = NULL;
	if ((int)type == GTHREAD_LAST)
		return (last);
	last = gthread_init(-1, NULL, NULL, type);
	return (last);
}