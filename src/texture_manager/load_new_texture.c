/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_new_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:46:30 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 17:47:18 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

int					load_texture_from_bmp(char *path, t_texture_mode mode)
{
	static int	id = 0;
	t_texture	*new;
	t_texture	*list;
	t_texture	tex;

	tex.texture = NULL;
	list = get_texture_list();
	if (!(tex.texture = libui_surface_image_load_32argb_scale(path, 1, 1)) ||
		!(new = (t_texture *)malloc(sizeof(t_texture) * (get_texture_list_size() + 1))))
	{
		if (tex.texture)
			SDL_FreeSurface(tex.texture);
		puts("Failed to load ");
		puts(path);
		puts(" into the texture manager!");
		return (-1);
	}
	if (list)
		mf_memcpy(new, list, get_texture_list_size() * sizeof(t_texture));
	tex.id = id++;
	tex.mode = mode;
	tex.size = (t_vec2i){.a = {tex.texture->w, tex.texture->h}};
	new[get_texture_list_size()] = tex;
	set_texture_list(new, get_texture_list_size() + 1);
	return (tex.id);
}
