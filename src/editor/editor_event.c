/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:20:45 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/20 14:02:43 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	editor_event(t_e *e, t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	(void)ws;
	(void)editor_interface;
	handle_events(&e->input_map);
	return (0);
}
