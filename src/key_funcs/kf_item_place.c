/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_item_place.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:49:19 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/19 20:50:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void		kf_item_place(void *param)
{
	t_e			*e;

	e = param;
	world_add_mesh(mesh_copy(e->editor.item_placer), &e->world, e->editor.secteur_courant);
}