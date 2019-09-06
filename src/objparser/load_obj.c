/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 13:39:21 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/06 10:50:07 by mfischer         ###   ########.fr       */
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

static void			cleanup_obj(t_obj *obj, int id)
{
	void	*tmp;

	while ((tmp = list2_pop(obj->vertices)))
		free(tmp);
	list2_destroy(&obj->vertices);
	while ((tmp = list2_pop(obj->vertices_uv)))
		free(tmp);
	list2_destroy(&obj->vertices_uv);
	while ((tmp = list2_pop(obj->normals)))
		free(tmp);
	list2_destroy(&obj->normals);
	while ((tmp = list2_pop(obj->indices)))
		free(tmp);
	list2_destroy(&obj->indices);
	if (obj->vertices_s)
		free(obj->vertices_s);
	if (obj->normals_s)
		free(obj->normals_s);
	if (obj->vertices_uv_s)
		free(obj->vertices_uv_s);
	read_line(obj, NULL, NULL);
	close(id);
}

static t_bool		obj_init(t_obj *obj, int fd)
{
	if (!(obj->vertices_s = list2_toarray(obj->vertices, &obj->size_v))
		|| !(obj->vertices_uv_s = list2_toarray(obj->vertices_uv,
			&obj->size_uv))
		|| !(obj->normals_s = list2_toarray(obj->normals, &obj->size_n)))
	{
		cleanup_obj(obj, fd);
		return (FALSE);
	}
	return (TRUE);
}

t_bool				iload(t_pars *a, t_obj *obj)
{
	while ((a->fml = get_next_line(a->fd, &a->line)) > 0)
	{
		if (!(read_line(obj, a->line, &a->tex)))
		{
			free(a->line);
			return (FALSE);
		}
		free(a->line);
		a->line = NULL;
	}
	if (a->line)
		free(a->line);
	return (TRUE);
}

t_obj				*load_obj(char *path)
{
	t_pars	a;
	t_obj	*obj;

	a.tex = -1;
	if ((a.fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	if (!(obj = init_obj()))
	{
		close(a.fd);
		return (NULL);
	}
	obj->has_normals = FALSE;
	obj->has_texture = FALSE;
	if (!(iload(&a, obj)))
	{
		cleanup_obj(obj, a.fd);
		return (NULL);
	}
	close(a.fd);
	if (a.fml == -1)
		return (NULL);
	if (!(obj_init(obj, a.fd)))
		return (NULL);
	read_line(obj, a.line, NULL);
	return (obj);
}
