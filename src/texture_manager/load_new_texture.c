/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_new_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:46:30 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/27 19:04:44 by mfischer         ###   ########.fr       */
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

void	zload(char *path, t_texture_mode mode, t_texture tex, t_texture *new)
{
	tex.id = get_texture_list_size();
	tex.mode = mode;
	tex.size = (t_vec2i){.a = {tex.texture->w, tex.texture->h}};
	mf_strcpy(tex.path, path);
	new[get_texture_list_size()] = tex;
	mf_strcpy(new[get_texture_list_size()].path, path);
	set_texture_list(new, get_texture_list_size() + 1);
}

int		load_texture_from_x(char *path, t_texture_mode mode)
{
	t_texture	*new;
	t_texture	*list;
	t_texture	tex;
	int			tmp;

	tex.texture = NULL;
	printf("%s\n", path);
	tmp = is_texture_already_created(path);
	if (tmp != -1)
		return (tmp);
	list = get_texture_list();
	tex.texture = IMG_Load(path);
	if (mf_strlen(path) > 511 || !(tex.texture) || !(new = (t_texture *)
		malloc(sizeof(t_texture) * (get_texture_list_size() + 1))))
		return (write(1, "failed to loadm into texture manager\n", 37));
	tex.texture = SDL_ConvertSurfaceFormat(tex.texture,
		SDL_PIXELFORMAT_ARGB8888, 0);
	if (list)
		mf_memcpy(new, list, get_texture_list_size() * sizeof(t_texture));
	if (list)
		free(list);
	zload(path, mode, tex, new);
	return (tex.id);
}

void	iload(char *path, t_texture_mode mode, t_texture tex, t_texture *new)
{
	tex.id = get_texture_list_size();
	tex.mode = mode;
	tex.size = (t_vec2i){.a = {tex.texture->w, tex.texture->h}};
	mf_strcpy(tex.path, path);
	new[get_texture_list_size()] = tex;
	mf_strcpy(new[get_texture_list_size()].path, path);
	set_texture_list(new, get_texture_list_size() + 1);
}

int		load_texture_from_bmp(char *path, t_texture_mode mode)
{
	t_texture	*new;
	t_texture	*list;
	t_texture	tex;
	int			tmp;

	tex.texture = NULL;
	tmp = is_texture_already_created(path);
	if (tmp != -1)
		return (tmp);
	list = get_texture_list();
	if (mf_strlen(path) > 511 || !(tex.texture =
		libui_surface_image_load_32argb_scale(path, 1, 1)) || !(new =
			(t_texture *)malloc(sizeof(t_texture) * (get_texture_list_size()
			+ 1))))
		return (write(1, "fail txt into the texture manager!\n", 35));
	if (list)
		mf_memcpy(new, list, get_texture_list_size() * sizeof(t_texture));
	if (list)
		free(list);
	iload(path, mode, tex, new);
	return (tex.id);
}
