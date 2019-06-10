/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_get_pixel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:48:36 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/10 19:07:08 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

int			texture_get_pixel(int y, int x)
{
	t_texture	texture;

	texture = get_current_texture();
	if (texture->mode == TX_CLAMP_EDGES)
	{
		if (x < 0)
			x = 0;
		if (x > texture->size.x)
			x = texture->size.x;
		if (y < 0)
			y = 0;
		if (y > texture->size.y)
			y = texture->size.y;
		return (((unsigned int *)texture->texture->pixels)[y * texture->size.y + x]);
	}
	return (((unsigned int *)texture->texture->pixels)[(y % texture->size.y) * texture->size.x + (x % texture->size.x)]);
}