/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_to_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 15:23:39 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/23 00:51:31 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

void				load_polygon(t_indice *i, t_polygon *p, t_obj *obj)
{
	SDL_memcpy(p->v01.a, obj->vertices_s[i->v[0] - 1], sizeof(double) * 3);
	p->v01.a[3] = 1;
	SDL_memcpy(p->v12.a, obj->vertices_s[i->v[1] - 1], sizeof(double) * 3);
	p->v12.a[3] = 1;
	SDL_memcpy(p->v20.a, obj->vertices_s[i->v[2] - 1], sizeof(double) * 3);
	p->v20.a[3] = 1;
	if (obj->has_texture)
	{
		SDL_memcpy(p->v01_uv.a, obj->vertices_uv_s[i->uv[0] - 1], sizeof(double) * 2);
		SDL_memcpy(p->v12_uv.a, obj->vertices_uv_s[i->uv[1] - 1], sizeof(double) * 2);
		SDL_memcpy(p->v20_uv.a, obj->vertices_uv_s[i->uv[2] - 1], sizeof(double) * 2);
	}
	else
	{
		p->v01_uv = (t_vec2d){.a = {0, 0}};
		p->v12_uv = (t_vec2d){.a = {0, 0}};
		p->v20_uv = (t_vec2d){.a = {0, 0}};
	}
}

void				charge_indices(t_object *object, t_obj *obj, int id)
{
	t_indice	*indice;
	t_node		*head;
	int			i;
	
	if (!(object->mesh->polygons = (t_polygon *)SDL_calloc(sizeof(t_polygon), obj->indices->size)))
		return ;
	object->mesh->polygonnum = obj->indices->size;
	head = obj->indices->list;
	i = -1;
	while (++i < object->mesh->polygonnum)
	{
		indice = head->data;
		load_polygon(indice, &object->mesh->polygons[i], obj);
		object->mesh->polygons[i].tex_id = id;
		object->mesh->polygons[i].transparency = 0;
		head = head->next;
	}
}

t_object			*obj_to_object(t_obj *obj, char *img, t_texture_mode mode)
{
	t_object	*object;
	int			id;

	if (!obj)
		return (NULL);
	if (!(object = (t_object *)SDL_calloc(sizeof(t_object), 1)))
		return (NULL);
	object->sub_object = NULL;
	object->sub_object_num = 0;
	if (!(object->mesh = (t_mesh *)SDL_calloc(sizeof(t_mesh), 1)))
	{
		free(object);
		return (NULL);
	}
	object->mesh->sector_id = -1;
	object->mesh->active = TRUE;
	object->meshnum = 1;
	mat4_init(&object->mesh->matrix);
	id = load_texture_from_bmp(img, mode);
	charge_indices(object, obj, id);
	return (object);
}
