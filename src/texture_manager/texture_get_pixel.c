/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_get_pixel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:48:36 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/30 14:40:08 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

int					texture_get_pixel(int y, int x, t_texture *texture)
{
	if (!texture)
		return (0xffff0000);
	if (texture->mode == TX_CLAMP_EDGES)
	{
		x = mf_clamp_int(x, 0, texture->size.n.x - 1);
		y = mf_clamp_int(y, 0, texture->size.n.y - 1);
	}
	return (((Uint32 *)texture->texture->pixels)[(((texture->size.n.y * 100
		- y) % texture->size.n.y)) * texture->size.n.x
		+ ((texture->size.n.x * 100 + x) % texture->size.n.x)]);
}
