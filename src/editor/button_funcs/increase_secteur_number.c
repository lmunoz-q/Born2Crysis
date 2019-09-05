/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase_secteur_number.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:27:06 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/05 14:35:12 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

static void	create_new_sector(t_editor_interface *ei, t_world *world)
{
	sector_create(world);
	world->sectors[world->sectornum - 1].physics.drag = ei->sector_drag;
	world->sectors[world->sectornum - 1].physics.gravity = ei->sector_gravity;
	world->sectors[world->sectornum - 1].physics.global_friction = ei->
		sector_global_friction;
	world->sectors[world->sectornum - 1].physics.speed_limit = ei->
		sector_speed_limit;
	world->sectors[world->sectornum - 1].physics.entering_effet = -1;
	world->sectors[world->sectornum - 1].physics.leaving_effect = -1;
	world->sectors[world->sectornum - 1].physics.frame_effect = -1;
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
	update_editor_interface_secteur(e, editor_interface);
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
