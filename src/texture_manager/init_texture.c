/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:20:14 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/18 20:09:32 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

static void	print_error(char *path)
{
	puts("Failed to create texture from ");
	puts(path);
	puts("...\n");
}

t_texture	init_texture(char *path, t_texture_mode mode)
{
	static int id = 0;
	t_texture texture;

	if(!(texture = (t_texture)malloc(sizeof(t_texture_s))))
	{
		print_error(path);
		return (NULL);
	}
	if (!(texture->texture = libui_surface_image_load_32argb_scale(path, 1, 1)))
	{
		print_error(path);
		free(texture);
		return (NULL);
	}
	texture->id = id;
	texture->mode = mode;
	texture->size.n.x = texture->texture->w;
	texture->size.n.y = texture->texture->h;
	texture->pitch = texture->texture->pitch;
	id++;
	return (texture);
}
