/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_new_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:46:30 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/30 14:23:07 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

int		is_texture_already_created(char *path)
{
	int			i;
	t_texture	*list;
	int			size;

	i = -1;
	list = get_texture_list();
	size = get_texture_list_size();
	while (++i < size)
		if (!strcmp(path, list[i].path))
			return (i);
	return (-1);
}

int		zload(char *path, t_texture_mode mode, t_texture *tex, t_texture *new)
{
	tex->id = get_texture_list_size();
	tex->mode = mode;
	tex->size = (t_vec2i){.a = {tex->texture->w, tex->texture->h}};
	mf_strcpy(tex->path, path);
	new[get_texture_list_size()] = *tex;
	mf_strcpy(new[get_texture_list_size()].path, path);
	set_texture_list(new, get_texture_list_size() + 1);
	return (0);
}

int		load_texture_from_x(char *path, t_texture_mode mode)
{
	t_texture	*new;
	t_texture	*list;
	t_texture	tex;
	void		*ptr;
	int			tmp;

	tex.texture = NULL;
	tmp = is_texture_already_created(path);
	if (tmp != -1)
		return (tmp);
	list = get_texture_list();
	tex.texture = IMG_Load(path);
	if (mf_strlen(path) > 1023 || !(tex.texture) || !(new = (t_texture *)
		malloc(sizeof(t_texture) * (get_texture_list_size() + 1))))
	{
		if (tex.texture)
			SDL_FreeSurface(tex.texture);
		return (-1);
	}
	if (!(ptr = SDL_ConvertSurfaceFormat(tex.texture,
		SDL_PIXELFORMAT_ARGB8888, 0)))
	{
		free(new);
		SDL_FreeSurface(tex.texture);
		return (-1);
	}
	SDL_FreeSurface(tex.texture);
	tex.texture = ptr;
	if (list)
		mf_memcpy(new, list, get_texture_list_size() * sizeof(t_texture));
	if (list)
		free(list);
	return (zload(path, mode, &tex, new) | tex.id);
}
