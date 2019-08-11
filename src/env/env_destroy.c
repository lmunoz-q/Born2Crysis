/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 10:51:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/08 10:52:11 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		env_destroy(t_e *e)
{
	int	i;

	libui_window_delete(e->win);
	i = -1;
	while (++i < 3)
		if (e->thread[i] != NULL)
			SDL_WaitThread(e->thread[i], NULL);
}
