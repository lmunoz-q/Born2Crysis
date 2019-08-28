/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_get_pixel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:48:36 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/28 14:45:11 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

int					texture_get_pixel(int y, int x, t_texture *texture)
{
	if (!texture)
		return (0xffff0000);
	if (texture->mode == TX_REPEAT)
	{
		return (((int *) texture->texture->pixels)[(((texture->size.n.y * 1000 - y)
				% texture->size.n.y)) * texture->size.n.x + ((texture->size.n.x * 1000 + x)
				% texture->size.n.x)]);
		/*if (y < 0)
			return (((int *) texture->texture->pixels)[(texture->size.n.y - (abs(y)
				% texture->size.n.y) - 1) * texture->size.n.x + (abs(x)
				% texture->size.n.x)]);
		else 
			return (((int *) texture->texture->pixels)[(texture->size.n.y - (abs(y)
				% texture->size.n.y)) * texture->size.n.x + (abs(x)
				% texture->size.n.x)]);*/
		
	}
	x = mf_clamp_int(x, 1, texture->size.n.x);
	y = mf_clamp_int(y, 1, texture->size.n.y);
	return (((int *)texture->texture->pixels)[(texture->size.n.y - y)
		* texture->size.n.x + x]);
}
