/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sector_physics.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 14:59:55 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/05 12:28:54 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

void	update_sector_physics(t_e *e)
{
	t_sector	*sector;

	sector = get_sector(e->editor.secteur_courant, &e->world);
	if (!sector)
		return ;
	sector->physics.drag = e->editor.sector_drag;
	sector->physics.global_friction = e->editor.sector_global_friction;
	sector->physics.gravity = e->editor.sector_gravity;
	sector->physics.speed_limit = e->editor.sector_speed_limit;
	if (sector->physics.entering_effect.id > -1 && sector->physics.entering_effect.id < (int32_t)e->world.lib.nb_functions)
		libui_label_set_text(&e->editor.label_script_1_file, e->world.lib.function_name[sector->physics.entering_effect.id]);
	else
		libui_label_set_text(&e->editor.label_script_1_file, SCRIPT_EMPTY);
	if (sector->physics.leaving_effect.id > -1 && sector->physics.leaving_effect.id < (int32_t)e->world.lib.nb_functions)
		libui_label_set_text(&e->editor.label_script_2_file, e->world.lib.function_name[sector->physics.leaving_effect.id]);
	else
		libui_label_set_text(&e->editor.label_script_2_file, SCRIPT_EMPTY);
	if (sector->physics.frame_effect.id > -1 && sector->physics.frame_effect.id < (int32_t)e->world.lib.nb_functions)
		libui_label_set_text(&e->editor.label_script_3_file, e->world.lib.function_name[sector->physics.frame_effect.id]);
	else
		libui_label_set_text(&e->editor.label_script_3_file, SCRIPT_EMPTY);
}
