/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_default_controls.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:45:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/13 20:16:29 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	init_default_controls(t_input_map	*m, t_e *e)
{
	m->keys[SDL_SCANCODE_ESCAPE] = gen_key(&kf_quit_game, e, FALSE);
	m->keys[SDL_SCANCODE_D] = gen_key(&kf_test, e, TRUE);
	m->keys[SDL_SCANCODE_A] = gen_key(&kf_test2, e, TRUE);
}
