/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_drop_catched.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 13:58:12 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/05 16:43:16 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"
#include <bmml_functions.h>

static int	check_ext(char *path)
{
	char	*tmp;

	printf("%s\n", mf_strrchr(path, '.'));
	if ((tmp = mf_strrchr(path, '.')))
		return (!mf_strcmp(tmp, SCRIPT_EXT));
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

static int	is_drop_catched_0(t_e *e, t_handle *h, int *match, int *id)
{
	SDL_Point		pos;
	char			*file;
	char			fn[12];
	int				r;
	t_world			*w;

	if (!check_ext(e->input_map.drop_file_path) || (w = get_world()) == NULL)
		return (-1);
	pos = (SDL_Point){h->x - h->x2, h->y - h->y2};
	if (SDL_PointInRect(&pos, &e->editor.script_1_area))
		*match = 1;
	else if (SDL_PointInRect(&pos, &e->editor.script_2_area))
		*match = 2;
	else if (SDL_PointInRect(&pos, e->editor.script_3_area))
		*match = 3;
	if ((*match == 0 && e->editor.item_placer == NULL)
		|| (file = read_file(e->input_map.drop_file_path)) == NULL)
		return (-1);
	filename(e->input_map.drop_file_path, fn);
	r = (add_function_to_library_direct(&w->lib, fn, file, 1) == ET_OK);
	free(file);
	if (!r)
		return (-1);
	*id = (int)(get_function(&w->lib, fn) - w->lib.function);
	return (0);
}

int			is_drop_catched(t_e *e, t_handle *h)
{
	int				match;
	int				id;
	t_sector		*sect;
	char			**name;

	match = 0;
	if (is_drop_catched_0(e, h, &match, &id))
		return (0);
	sect = &get_world()->sectors[e->editor.secteur_courant];
	name = get_world()->lib.function_name;
	if (match > 0 && match < 4)
		libui_label_set_text(&e->editor.label_script_file[match - 1], name[id]);
	if (match == 1)
		sect->physics.entering_effect = (t_effet){id, {0}};
	else if (match == 2)
		sect->physics.leaving_effect = (t_effet){id, {0}};
	else if (match == 3)
		sect->physics.frame_effect = (t_effet){id, {0}};
	else
	{
		libui_label_set_text(&e->editor.label_script_obj_file, name[id]);
		if (e->editor.item_placer)
			e->editor.item_placer->on_contact = (t_effet){id, {0}};
	}
	return (1);
}
