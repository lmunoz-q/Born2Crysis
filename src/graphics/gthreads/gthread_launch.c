/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gthread_launch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:57:33 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/25 00:02:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void				gthread_launch(t_gthreads *gt)
{
	pthread_mutex_lock(&gt->wait_mtx);
	gt->wait = TRUE;
	pthread_mutex_unlock(&gt->wait_mtx);
	pthread_mutex_lock(&gt->work_mtx);
	gt->work = TRUE;
	pthread_cond_broadcast(&gt->work_cnd);
	pthread_mutex_unlock(&gt->work_mtx);
}