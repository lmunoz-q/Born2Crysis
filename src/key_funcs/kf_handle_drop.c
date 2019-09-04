/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_handle_drop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:58:12 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 18:08:18 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"
#include <bmml_functions.h>

void	ikf_handle_drop(t_e *e)
{
	char	*str;

	if (!e->editor.is_modified &&
		mf_strstr(e->input_map.drop_file_path, ".obj"))
	{
		if (e->editor.item_placer)
		{
			if (((t_mesh *)e->editor.item_placer)->walls)
				free(((t_mesh *)e->editor.item_placer)->walls);
			if (((t_mesh *)e->editor.item_placer)->polygons)
				free(((t_mesh *)e->editor.item_placer)->polygons);
			free(e->editor.item_placer);
		}
		e->editor.item_placer = NULL;
		e->editor.item_placer = obj_to_mesh(object_manager_get_obj(e->input_map.
			drop_file_path), "assets/textures/redbrick.bmp", TX_REPEAT);
	}
	else if ((str = mf_strrchr(e->input_map.drop_file_path, '.')) && !mf_strcmp("bmml", str))
	{

	}
	else
		mesh_change_texture(e->editor.item_placer, load_texture_from_x(e->
			input_map.drop_file_path, TX_REPEAT));
}

static int	check_ext(char *path)
{
	char	*tmp;

	printf("%s\n", mf_strrchr(path, '.'));
	if ((tmp = mf_strrchr(path, '.')))
		return (!mf_strcmp(tmp, SCRIPT_EXT));
	return (0);
}

static int	is_in_area(SDL_Rect rect, SDL_Point pos)
{
	if (pos.x >= rect.x && pos.x <= rect.x + rect.w
	&& pos.y >= rect.y && pos.y <= rect.y + rect.h)
		return (1);
	return (0);
}

static char	*read_file(const char *path)
{
	char	buff[1024];
	char	*out;
	int		fd;
	size_t	size;
	ssize_t	r;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	out = NULL;
	size = 0;
	while ((r = read(fd, buff, 1024)) > 0)
	{
		out = realloc_f(out, size + r + 1);
		mf_memcpy(&out[size], buff, (size_t)r);
		size += r;
	}
	if (size)
		out[size] = '\0';
	close(fd);
	return (out);
}

static void	filename(char *path, char fn[12])
{
	char	*out;
	size_t	len;

	if (!(out = mf_strrchr(path, '/')))
		out = path;
	++out;
	len = mf_strrchr(out, '.') - out;
	strncpy(fn, out, len > 11 ? 11 : len);
	fn[len > 11 ? 11 : len] = '\0';
}

static int	is_drop_catched(t_e *e, t_handle *h)
{
	SDL_Point		pos;
	int				match;
	char			*file;
	char			fn[12];
	int				r;
	t_library		*lib;
	t_sector		*sect;

	if (!check_ext(e->input_map.drop_file_path))
		return (0);
	pos = (SDL_Point){h->x - h->x2, h->y - h->y2};
	match = 0;
	lib = &get_world()->lib;
	sect = &get_world()->sectors[e->editor.secteur_courant];
	if (is_in_area(e->editor.script_1_area, pos))
		match = 1;
	else if (is_in_area(e->editor.script_2_area, pos))
		match = 2;
	else if (is_in_area(e->editor.script_3_area, pos))
		match = 3;
	if (match == 0 && e->editor.item_placer == NULL)
		return (0);
	if ((file = read_file(e->input_map.drop_file_path)) == NULL)
		return (0);
	filename(e->input_map.drop_file_path, fn);
	r = (add_function_to_library_direct(lib, fn, file, 1) == ET_OK);
	free(file);
	if (!r)
		return (0);
	r = (int32_t)(get_function(lib, fn) - lib->function) / sizeof(t_function);
	if (match == 1)
	{
		libui_label_set_text(&e->editor.label_script_1_file, fn);
		sect->physics.entering_effet = r;
	}
	else if (match == 2)
	{
		libui_label_set_text(&e->editor.label_script_2_file, fn);
		sect->physics.leaving_effect = r;
	}
	else if (match == 3)
	{
		libui_label_set_text(&e->editor.label_script_3_file, fn);
		sect->physics.frame_effect = r;
	}
	else
		e->editor.item_placer->on_contact = r;
	return (1);
}

void		kf_handle_drop(void *param)
{
	t_e			*e;
	t_handle	h;

	h.x = 0;
	h.y = 0;
	h.x2 = 0;
	h.y2 = 0;
	h.size = 160;
	e = param;
	if (!(h.message = malloc(h.size + 1)))
		return ;
	SDL_memset(h.message, '\0', h.size + 1);
	SDL_GetGlobalMouseState(&h.x, &h.y);
	SDL_GetWindowPosition(e->win->ptr, &h.x2, &h.y2);
	if (!is_drop_catched(e, &h))
	{
		snprintf(h.message, h.size, "File : %s.", e->input_map.drop_file_path);
		libui_label_set_text(&(e->editor.selected_file_label), h.message);
		ikf_handle_drop(e);
	}
	free(h.message);
	free(e->input_map.drop_file_path);
}
