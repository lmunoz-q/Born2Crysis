/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:10:27 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/16 16:10:48 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

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
