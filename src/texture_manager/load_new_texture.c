/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_new_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:46:30 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/10 19:22:50 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

int					load_texture_from_bmp(char *path, t_texture_mode mode)
{
	t_texture	texture;
	t_list2		*l;

	if (!(texture = init_texture(path, mode)))
		return (-1);
	if (!(l = get_texture_list()) || !list2_push(l, texture))
	{
		destroy_texture(&texture);
		puts("Failed to load ");
		puts(path);
		puts(" into the texture manager!");
		return (-1);
	}
	return (texture->id);
}
