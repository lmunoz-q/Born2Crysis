/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 01:03:48 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/12 01:31:50 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		render_object(t_object *object, t_camera *cam, SDL_Surface *surface, t_light_comp *lcomp)
{
	int i;

	i = -1;
	while (++i < object->sub_object_num)
		render_object(&object->sub_object[i], cam, surface, lcomp);
		
	i = -1;
	while (++i < object->meshnum)
		render_mesh(&object->mesh[i], cam, surface, lcomp);
}