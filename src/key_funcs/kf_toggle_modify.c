/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_toggle_modify.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:36:10 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/06 13:38:31 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_toggle_modify(void *param)
{
	t_e		*e;

	e = param;
	if (e->editor.is_modified)
		e->editor.is_modified = FALSE;
	else
	{
		e->editor.is_modified = TRUE;
		if (e->editor.item_placer)
		{
			free(e->editor.item_placer->polygons);
			mesh_delete_physics(e->editor.item_placer);
			free(e->editor.item_placer);
			e->editor.item_placer = NULL;
		}
	}
}
