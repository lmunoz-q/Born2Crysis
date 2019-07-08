/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:36:02 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/24 18:17:56 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_POOL_H
# define THREAD_POOL_H

#include "mflib.h"

t_thread_pool		*set_thread_pool(int slaves, int max_work);
t_thread_pool		*get_thread_pool();

#endif
