/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_handle_drop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:58:12 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 18:05:30 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void		ikf_handle_drop(t_e *e)
{
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
	else
		mesh_change_texture(e->editor.item_placer, load_texture_from_x(e->
			input_map.drop_file_path, TX_REPEAT));
}

static int	check_name(char **filename, char *str)
{
	char	*tmp;

	if (str == NULL)
		return (-1);
	*filename = mf_strrchr(str, '/');
	if (*filename == NULL)
		*filename = str;
	else
		(*filename)++;
	tmp = mf_strrchr(*filename, '.');
	if (tmp == NULL || mf_strcmp(tmp, SCRIPT_EXT) != 0)
		return (-1);
	*tmp = '\0';
	return (0);
}

static int	is_in_area(SDL_Rect rect, SDL_Point pos)
{
	if (pos.x >= rect.x && pos.x <= rect.x + rect.w
	&& pos.y >= rect.y && pos.y <= rect.y + rect.h)
		return (1);
	return (0);
}

static int	is_drop_catched(t_e *e, t_handle *h)
{
	char			*filename;
	SDL_Point		pos;

	if (check_name(&filename, e->input_map.drop_file_path))
		return (0);
	pos = (SDL_Point){h->x - h->x2, h->y - h->y2};
	if (is_in_area(e->editor.script_1_area, pos))
	{
		mf_strncpy(e->editor.script_1_name, filename, 12);
		libui_label_set_text(&e->editor.label_script_1_file,
			e->editor.script_1_name);
	}
	if (is_in_area(e->editor.script_2_area, pos))
	{
		mf_strncpy(e->editor.script_2_name, filename, 12);
		libui_label_set_text(&e->editor.label_script_2_file,
			e->editor.script_2_name);
	}
	if (is_in_area(e->editor.script_3_area, pos))
	{
		mf_strncpy(e->editor.script_3_name, filename, 12);
		libui_label_set_text(&e->editor.label_script_3_file,
			e->editor.script_3_name);
	}
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
