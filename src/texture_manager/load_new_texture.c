/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_new_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:46:30 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 19:46:18 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

static int			check_if_esist(t_texture *list, char *path)
{
	int i;

	i = -1;
	while ((size_t)++i < get_texture_list_size())
	{
		if (strcmp(list[i].path, path) == 0)
			return (list[i].id);
	}
	return (-1);
}

int					load_texture_from_bmp(char *path, t_texture_mode mode)
{
	static int	id = 0;
	t_texture	*new;
	t_texture	*list;
	t_texture	tex;
	int			tmp;

	tex.texture = NULL;
	list = get_texture_list();
	if ((tmp = check_if_esist(list, path)) != -1)
		return (tmp);
	if (mf_strlen(path) > 99 ||
		!(tex.texture = libui_surface_image_load_32argb_scale(path, 1, 1)) ||
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
	mf_strcpy(tex.path, path);
	new[get_texture_list_size()] = tex;
	set_texture_list(new, get_texture_list_size() + 1);
	return (tex.id);
}
