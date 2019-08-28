/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 13:39:21 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/27 18:32:18 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

t_obj				*init_obj(void)
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
	int		tex;

	tex = -1;
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
		read_line(obj, line, &tex);
		free(line);
	}
	obj->vertices_s = list2_toarray(obj->vertices, &obj->size_v);
	obj->vertices_uv_s = list2_toarray(obj->vertices_uv, &obj->size_uv);
	obj->normals_s = list2_toarray(obj->normals, &obj->size_n);
	close(fd);
	return (obj);
}
