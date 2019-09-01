/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_default_editor_controls.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:41:38 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/21 18:10:12 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	init_default_editor_controls(t_input_map *m, t_e *e)
{
	m->keys[SDL_SCANCODE_ESCAPE] = gen_key(&kf_quit_editor, e, FALSE);
	m->keys[SDL_SCANCODE_W] = gen_key(&kf_fly_forward, e, TRUE);
	m->keys[SDL_SCANCODE_A] = gen_key(&kf_fly_left, e, TRUE);
	m->keys[SDL_SCANCODE_D] = gen_key(&kf_fly_right, e, TRUE);
	m->keys[SDL_SCANCODE_S] = gen_key(&kf_fly_backwards, e, TRUE);
	m->keys[SDL_SCANCODE_SPACE] = gen_key(&kf_fly_up, e, TRUE);
	m->keys[SDL_SCANCODE_LCTRL] = gen_key(&kf_fly_down, e, TRUE);
	m->keys[SDL_SCANCODE_KP_8] = gen_key(&kf_preview_rotate_yaw_r, e, TRUE);
	m->keys[SDL_SCANCODE_KP_2] = gen_key(&kf_preview_rotate_yaw_l, e, TRUE);
	m->keys[SDL_SCANCODE_KP_6] = gen_key(&kf_preview_rotate_pitch_r, e, TRUE);
	m->keys[SDL_SCANCODE_KP_4] = gen_key(&kf_preview_rotate_pitch_l, e, TRUE);
	m->keys[SDL_SCANCODE_KP_9] = gen_key(&kf_preview_rotate_roll_r, e, TRUE);
	m->keys[SDL_SCANCODE_KP_7] = gen_key(&kf_preview_rotate_roll_l, e, TRUE);
	m->keys[SDL_SCANCODE_V] = gen_key(&kf_toggle_editor_view, e, FALSE);
	m->keys[KF_FILEDROP] = gen_key(&kf_handle_drop, e, FALSE);
	m->buttons[KF_MOUSEWHEEL] = gen_key(&kf_scale_item, e, FALSE);
	m->buttons[SDL_BUTTON_LEFT] = gen_key(&kf_item_place, e, FALSE);
	m->buttons[SDL_BUTTON_MIDDLE] = gen_key(&kf_item_copy, e, FALSE);
	m->buttons[SDL_BUTTON_RIGHT] = gen_key(&kf_item_delete, e, FALSE);
}
