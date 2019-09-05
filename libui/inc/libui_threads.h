/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_threads.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:33:45 by hmartzol          #+#    #+#             */
/*   Updated: 2019/03/05 18:33:47 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_THREADS_H
# define LIBUI_THREADS_H

# include <libui_typedef.h>

struct	s_libui_thread
{
	SDL_Thread	*ptr;
	int			(*fn)(void *user_data);
	const char	*name;
	SDL_mutex	*mutex;
	void		*user_data;
	int			external_update;
};

#endif
