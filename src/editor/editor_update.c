/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 23:36:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/17 23:54:48 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int editor_update(t_e *e, t_libui_widgets_surface *ws,
				  t_editor_interface *editor_interface)
{
	(void)e;
	(void)ws;
	editor_interface->preview_mat = mat4_rotate_pitch(editor_interface->preview_mat, 1);
	return (0);
}