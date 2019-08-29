/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_funcs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:40:54 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/21 16:42:57 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_FUNCS_H
# define KEY_FUNCS_H

# include "doom_nukem.h"
# include "event_handler.h"

typedef struct	s_handle
{
	int			x;
	int			y;
	int			x2;
	int			y2;
	int			size;
	char		*message;
}				t_handle;

void	init_default_controls(t_input_map	*m, t_e *e);
void	init_default_editor_controls(t_input_map	*m, t_e *e);

void	kf_quit_game(void *param);
void	kf_quit_editor(void *param);

void	kf_walk_forward(void *param);
void	kf_walk_backward(void *param);
void	kf_walk_left(void *param);
void	kf_walk_right(void *param);
void	kf_jump(void *param);
void	kf_crouch(void *param);
void	kf_run(void *param);

void	kf_fly_forward(void *param);
void	kf_fly_backwards(void *param);
void	kf_fly_left(void *param);
void	kf_fly_right(void *param);
void	kf_fly_up(void *param);
void	kf_fly_down(void *param);

void	kf_scale_item(void *param);
void	kf_preview_rotate_yaw_r(void *param);
void	kf_preview_rotate_yaw_l(void *param);
void	kf_preview_rotate_pitch_r(void *param);
void	kf_preview_rotate_pitch_l(void *param);
void	kf_preview_rotate_roll_r(void *param);
void	kf_preview_rotate_roll_l(void *param);

void	kf_item_place(void *param);
void    kf_handle_drop(void *param);
void    kf_toggle_editor_view(void *param);
void    kf_item_delete(void *param);
void    kf_item_copy(void *param);

#endif
