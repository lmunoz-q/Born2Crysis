/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_funcs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:40:54 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 17:05:23 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_FUNCS_H
# define KEY_FUNCS_H

# include "doom-nukem.h"
# include "event_handler.h"

void	init_default_controls(t_input_map	*m, t_e *e);

void	kf_quit_game(void *param);

void	kf_walk_forward(void *param);
void	kf_walk_backward(void *param);
void	kf_walk_left(void *param);
void	kf_walk_right(void *param);
void	kf_jump(void *param);
void	kf_run(void *param);

#endif
