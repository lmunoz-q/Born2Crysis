/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_default_controls.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:45:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 14:47:04 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	init_default_controls(t_input_map *m, t_e *e)
{
	m->keys[SDL_SCANCODE_ESCAPE] = gen_key(&kf_quit_game, e, FALSE);
	m->keys[SDL_SCANCODE_W] = gen_key(&kf_walk_forward, e, TRUE);
	m->keys[SDL_SCANCODE_S] = gen_key(&kf_walk_backward, e, TRUE);
	m->keys[SDL_SCANCODE_A] = gen_key(&kf_walk_left, e, TRUE);
	m->keys[SDL_SCANCODE_D] = gen_key(&kf_walk_right, e, TRUE);
	m->keys[SDL_SCANCODE_SPACE] = gen_key(&kf_jump, e, TRUE);
	m->keys[SDL_SCANCODE_LSHIFT] = gen_key(&kf_run, e, TRUE);
	m->keys[SDL_SCANCODE_LCTRL] = gen_key(&kf_crouch, e, FALSE);
	m->keys[SDL_SCANCODE_R] = gen_key(&kf_eidos_rewind, e, TRUE);
}
