/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase_secteur_number.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:27:06 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/27 13:03:51 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	create_new_sector(t_editor_interface *ei, t_world *world)
{
	sector_create(world);
	world->sectors[world->sectornum - 1].physics.drag = ei->sector_drag;
	world->sectors[world->sectornum - 1].physics.gravity = ei->sector_gravity;
	world->sectors[world->sectornum - 1].physics.global_friction = ei->
		sector_global_friction;
	world->sectors[world->sectornum - 1].physics.speed_limit = ei->
		sector_speed_limit;
	world->sectors[world->sectornum - 1].physics.entering_effet = EFF_NOTHING;
	world->sectors[world->sectornum - 1].physics.leaving_effect = EFF_NOTHING;
	world->sectors[world->sectornum - 1].physics.frame_effect = EFF_NOTHING;
}

int			increase_secteur_number(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	t_e					*e;
	t_editor_interface	*editor_interface;

	(void)event;
	(void)widget;
	e = data;
	editor_interface = &((t_e *)data)->editor;
	if (editor_interface->secteur_courant < MAX_SECTEURS)
		editor_interface->secteur_courant += 1;
	if (editor_interface->secteur_courant == e->world.sectornum)
		create_new_sector(editor_interface, &e->world);
	editor_interface->sector_drag = e->world.sectors[editor_interface->
		secteur_courant].physics.drag;
	editor_interface->sector_global_friction = e->world.
		sectors[editor_interface->secteur_courant].physics.global_friction;
	editor_interface->sector_gravity = e->world.sectors[editor_interface->
		secteur_courant].physics.gravity;
	update_secteur_courant_text(&(editor_interface->secteur_selec_label),
		editor_interface->secteur_courant);
	return (0);
}

int			increase_secteur2_number(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	t_e					*e;
	t_editor_interface	*editor_interface;

	(void)event;
	(void)widget;
	e = data;
	editor_interface = &e->editor;
	if (editor_interface->secteur2_courant < MAX_SECTEURS)
		editor_interface->secteur2_courant += 1;
	if (editor_interface->secteur2_courant == e->world.sectornum)
		create_new_sector(editor_interface, &e->world);
	update_secteur2_courant_text(&(editor_interface->secteur2_selec_label),
		editor_interface->secteur2_courant);
	return (0);
}
