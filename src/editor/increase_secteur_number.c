/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase_secteur_number.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:27:06 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/21 16:40:57 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int	increase_secteur_number(SDL_Event *event, t_libui_widget *widget,
							void *data)
{
	t_editor_interface	*editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->secteur_courant < MAX_SECTEURS)
		editor_interface->secteur_courant += 1;
	update_secteur_courant_text(&(editor_interface->secteur_selec_label),
								editor_interface->secteur_courant);
	return (0);
}

int increase_secteur2_number(SDL_Event *event, t_libui_widget *widget,
							void *data)
{
	t_editor_interface *editor_interface;

	(void)event;
	(void)widget;
	editor_interface = (t_editor_interface *)data;
	if (editor_interface->secteur2_courant < MAX_SECTEURS)
		editor_interface->secteur2_courant += 1;
	update_secteur2_courant_text(&(editor_interface->secteur2_selec_label),
								editor_interface->secteur2_courant);
	return (0);
}
