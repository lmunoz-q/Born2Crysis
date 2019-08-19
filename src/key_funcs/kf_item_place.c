/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_item_place.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:49:19 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/19 11:13:10 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void		kf_item_place(void *param)
{
	t_e			*e;
	t_object	*object;
	t_object	*object2;

	e = param;
	if (e->editor.is_object)
	{
		object = e->editor.item_placer;
		object2 = obj_to_object(object->obj, object->texture, object->mode);
		object2->mesh[0].matrix = object->mesh[0].matrix;
		world_add_object(object2, &e->world, e->editor.secteur_courant);
	}
	else
	{
		world_add_mesh(mesh_copy(e->editor.item_placer), &e->world, e->editor.secteur_courant);
	}
}