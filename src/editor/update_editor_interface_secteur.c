/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_editor_interface_secteur.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:35:22 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/05 18:02:15 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "doom_nukem.h"

void		update_editor_interface_secteur_sub(t_e *e,
	t_editor_interface *edi)
{
	edi->sector_drag = e->world.sectors[edi->
		secteur_courant].physics.drag;
	edi->sector_global_friction = e->world.
		sectors[edi->secteur_courant].physics.global_friction;
	edi->sector_gravity = e->world.sectors[edi->
		secteur_courant].physics.gravity;
	update_sector_drag(&e->editor);
	update_sector_friction(&e->editor);
	update_sector_gravity(&e->editor);
}

void		update_editor_interface_secteur(t_e *e,
	t_editor_interface *edi)
{
	t_sector		*sector;

	update_editor_interface_secteur_sub(e, edi);
	sector = &e->world.sectors[edi->secteur_courant];
	if (sector->physics.entering_effect.id > -1 && sector->physics.
	entering_effect.id < (int32_t)e->world.lib.nb_functions)
		libui_label_set_text(&e->editor.label_script_file[0], e->world.lib.
		function_name[sector->physics.entering_effect.id]);
	else
		libui_label_set_text(&e->editor.label_script_file[0], SCRIPT_EMPTY);
	if (sector->physics.leaving_effect.id > -1 && sector->physics.
	leaving_effect.id < (int32_t)e->world.lib.nb_functions)
		libui_label_set_text(&e->editor.label_script_file[1], e->world.lib.
		function_name[sector->physics.leaving_effect.id]);
	else
		libui_label_set_text(&e->editor.label_script_file[1], SCRIPT_EMPTY);
	if (sector->physics.frame_effect.id > -1 && sector->physics.frame_effect.
	id < (int32_t)e->world.lib.nb_functions)
		libui_label_set_text(&e->editor.label_script_file[2], e->world.lib.
		function_name[sector->physics.frame_effect.id]);
	else
		libui_label_set_text(&e->editor.label_script_file[2], SCRIPT_EMPTY);
	update_secteur_courant_text(&(edi->secteur_selec_label),
		edi->secteur_courant);
}
