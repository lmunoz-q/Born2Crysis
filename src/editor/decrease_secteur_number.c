/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decrease_secteur_number.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:29:22 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/15 16:00:14 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int	decrease_secteur_number(SDL_Event *event, t_libui_widget *widget,
							void *data)
{
	t_editor_interface	*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->secteur_courant > 0)
		editor_interface->secteur_courant -= 1;
	update_secteur_courant_text(&(editor_interface->secteur_selec_label),
								editor_interface->secteur_courant);
	return (0);
}
