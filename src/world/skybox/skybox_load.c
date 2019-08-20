/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:45:23 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 16:17:56 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void				skybox_load(t_world *world, char *path)
{
	t_obj		*obj;

	if (!(obj = load_obj("assets/skybox/skybox.obj")))
		return ;
	world->skybox = obj_to_mesh(obj, path, TX_CLAMP_EDGES);
}
