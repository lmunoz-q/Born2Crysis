/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:10:27 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/28 14:41:41 by mfischer         ###   ########.fr       */
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

void				get_indices(t_list2 *l, char *line, int *tex)
{
	int format;

	format = get_type(line);
	if (format == 0)
		get_ints_format_one(l, line, tex);
	if (format == 1)
		get_ints_format_two(l, line, tex);
	if (format == 2)
		get_ints_format_three(l, line, tex);
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

char				*get_mtl_name(char *line)
{
	while (*line && mf_isspace(*line))
		line++;
	while (*line && !mf_isspace(*line))
		line++;
	while (*line && mf_isspace(*line))
		line++;
	return (line);
}

int					get_mtl_tex(char *line, char *path)
{
	int		fd;
	char	*nl;
	t_bool	right;
	int		tmp;

	tmp = -1;
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		return (-1);
	}
	right = FALSE;
	while (get_next_line(fd, &nl))
	{
		if (mf_strstr(nl, get_mtl_name(line)) && tmp == -1)
			right = TRUE;
		if (mf_strstr(nl, "map_Kd") && right)
		{
			right = FALSE;
			tmp = load_texture_from_x(get_mtl_name(nl), TX_REPEAT);
		}
		free(nl);
	}
	close(fd);
	return (tmp);
}

void				read_line(t_obj *obj, char *line, int *tex)
{
	static char	*mtl = NULL;
	
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
	{
		get_indices(obj->indices, line + 1, tex);
	}
	if (mf_strstr(line, "mtllib"))
	{
		if (mtl)
			free(mtl);
		if (!(mtl = mf_strjoin("assets/mtls/", get_mtl_name(line))))
			return ;
	}
	if (mf_strstr(line, "usemtl"))
	{
		*tex = get_mtl_tex(line, mtl);
		printf("ll: %d\n", *tex);
	}
}
