/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_toggle_editor_view.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:40:31 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 18:43:27 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_toggle_editor_view(void *param)
{
	t_e *e;

	e = param;
	toggle_capture_mouse(NULL, NULL, e->win->ptr);
	if (e->editor.is_in_view)
		e->editor.is_in_view = FALSE;
	else
		e->editor.is_in_view = TRUE;
}
