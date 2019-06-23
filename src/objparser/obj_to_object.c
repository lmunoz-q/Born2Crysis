/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_to_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 15:23:39 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/23 13:36:08 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

void				load_polygon(t_indice *i, t_polygon *p, t_obj *obj)
{
	vec3_copy(p->v01, obj->vertices_s[i->v[0] - 1]);
	p->v01[3] = 1;
	vec3_copy(p->v12, obj->vertices_s[i->v[1] - 1]);
	p->v12[3] = 1;
	vec3_copy(p->v20, obj->vertices_s[i->v[2] - 1]);
	p->v20[3] = 1;
	if (obj->has_texture)
	{
		vec2_copy(p->v01_uv, obj->vertices_uv_s[i->uv[0] - 1]);
		vec2_copy(p->v12_uv, obj->vertices_uv_s[i->uv[1] - 1]);
		vec2_copy(p->v20_uv, obj->vertices_uv_s[i->uv[2] - 1]);
	}
	else
	{
		vec2_clear(p->v01_uv);
		vec2_clear(p->v12_uv);
		vec2_clear(p->v20_uv);
	}
}

void				charge_indices(t_object *object, t_obj *obj, int id)
{
	t_indice	*indice;
	t_node		*head;
	int			i;
	
	if (!(object->mesh->polygons = (t_polygon *)malloc(sizeof(t_polygon) * obj->indices->size)))
		return ;
	object->mesh->polygonnum = obj->indices->size;
	head = obj->indices->list;
	i = -1;
	while (++i < object->mesh->polygonnum)
	{
		indice = head->data;
		load_polygon(indice, &object->mesh->polygons[i], obj);
		object->mesh->polygons[i].tex_id = id;
		head = head->next;
	}
}

t_object			*obj_to_object(t_obj *obj, char *img, t_texture_mode mode)
{
	t_object	*object;
	int			id;

	if (!obj)
		return (NULL);
	if (!(object = (t_object *)malloc(sizeof(t_object))))
		return (NULL);
	object->sub_object = NULL;
	object->sub_object_num = 0;
	if (!(object->mesh = (t_mesh *)malloc(sizeof(t_mesh))))
	{
		free(object);
		return (NULL);
	}
	object->meshnum = 1;
	mat4_init(object->mesh->matrix);
	id = load_texture_from_bmp(img, mode);
	charge_indices(object, obj, id);
	return (object);
}
