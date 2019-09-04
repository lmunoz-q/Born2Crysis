/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_quit_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:42:31 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 20:29:48 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_quit_game(void *param)
{
	((t_e *)param)->game_running = FALSE;
	if (((t_e *)param)->endscreen_running)
		((t_e *)param)->endscreen_running = FALSE;
}
