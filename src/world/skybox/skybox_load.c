/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:45:23 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 19:00:29 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void				skybox_load(t_world *world, char *path)
{
	t_obj		*obj;

	if(!(obj = load_obj("assets/skybox/skybox.obj")))
		return ;
	world->skybox = obj_to_object(obj, path, TX_CLAMP_EDGES);
}
