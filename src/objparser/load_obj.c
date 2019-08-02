/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 13:39:21 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/18 17:48:27 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

void				get_vertices(t_list2 *l, char *line, int num)
{
	double	*vertices;
	int		i;

	if (!(vertices = (double *)SDL_calloc(sizeof(double), num)))
		return ;
	i = -1;
	while (++i < num)
	{
		while (mf_isspace(*line))
			line++;
		vertices[i] = mf_atof(line);
		while (mf_isdigit(*line) || *line == '.' || *line == '-')
			line++;
	}
	list2_pushback(l, vertices);
}

int					get_type(char *line)
{
	int i;

	i = 0;
	while (*line && !mf_isdigit(*line))
		line++;
	while (*line && *line != ' ')
		if (*line++ == '/')
			i++;
	return (i);
}

void				get_indices(t_list2 *l, char *line)
{
	int format;

	format = get_type(line);
	if (format == 0)
		get_ints_format_one(l, line);
	if (format == 1)
		get_ints_format_two(l, line);
	if (format == 2)
		get_ints_format_three(l, line);
	
}

void				read_line(t_obj *obj, char *line)
{
	while (isspace(*line))
		line++;
	if (*line == '#')
		return ;
	if (*line == 'v' && *(line + 1) == ' ')
		get_vertices(obj->vertices, line + sizeof(char), 3);
	if (*line == 'v' && *(line + 1) == 't')
	{
		get_vertices(obj->vertices_uv, line + (sizeof(char) * 2), 2);
		obj->has_texture = TRUE;
	}
	if (*line == 'v' && *(line + 1) == 'n')
	{
		get_vertices(obj->normals, line + (sizeof(char) * 2), 3);
		obj->has_normals = TRUE;
	}
	if (*line == 'f' && *(line + 1) == ' ')
		get_indices(obj->indices, line + 1);
}

t_obj				*init_obj()
{
	t_obj *obj;

	if (!(obj = (t_obj *)SDL_calloc(sizeof(t_obj), 1)))
		return (NULL);
	obj->vertices = list2_create();
	obj->vertices_uv = list2_create();
	obj->normals = list2_create();
	obj->indices = list2_create();
	return (obj);
}

t_obj				*load_obj(char *path)
{
	int		fd;
	char	*line;
	t_obj	*obj;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	if (!(obj = init_obj()))
	{
		close(fd);
		return (NULL);
	}
	obj->has_normals = FALSE;
	obj->has_texture = FALSE;
	while (get_next_line(fd, &line))
	{
		read_line(obj, line);
		free(line);
	}
	obj->vertices_s = list2_toarray(obj->vertices, &obj->size_v);
	obj->vertices_uv_s = list2_toarray(obj->vertices_uv, &obj->size_uv);
	obj->normals_s = list2_toarray(obj->normals, &obj->size_n);
	close(fd);
	return (obj);
}
