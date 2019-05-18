/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_to_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 15:23:39 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/18 20:54:56 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

void				load_polygon(t_indice *i, t_polygon *p, t_obj *obj)
{
	vec3_copy(p->v01_o, obj->vertices_s[i->v[0] - 1]);
	p->v01_o[3] = 1;
	vec3_copy(p->v12_o, obj->vertices_s[i->v[1] - 1]);
	p->v12_o[3] = 1;
	vec3_copy(p->v20_o, obj->vertices_s[i->v[2] - 1]);
	p->v20_o[3] = 1;
	if (obj->has_texture)
	{
		vec2_copy(p->v01_uv_o, obj->vertices_uv_s[i->uv[0] - 1]);
		vec2_copy(p->v12_uv_o, obj->vertices_uv_s[i->uv[1] - 1]);
		vec2_copy(p->v20_uv_o, obj->vertices_uv_s[i->uv[2] - 1]);
	}
	else
	{
		vec2_clear(p->v01_uv_o);
		vec2_clear(p->v12_uv_o);
		vec2_clear(p->v20_uv_o);
	}
	if (obj->has_normals)
	{
		vec3_copy(p->v01_n_o, obj->normals_s[i->n[0] - 1]);
		vec3_copy(p->v12_n_o, obj->normals_s[i->n[1] - 1]);
		vec3_copy(p->v20_n_o, obj->normals_s[i->n[2] - 1]);
	}
}

void				charge_indices(t_list2 *l, t_obj *obj, SDL_Surface *tex)
{
	t_node		*head;
	t_indice	*i;
	t_polygon	*p;

	head = obj->indices->list;
	while (head)
	{
		i = head->data;
		if ((p = (t_polygon *)malloc(sizeof(t_polygon))))
		{
			p->preloaded_normal = FALSE;
			load_polygon(i, p, obj);
			p->is_clipped = FALSE;
			p->texture = tex;
			list2_push(l, p);
		}
		head = head->next;
	}
}

t_object			*obj_to_object(t_obj *obj, char *img, int sizex, int sizey)
{
	t_object	*object;
	SDL_Surface	*tex;

	if (!obj)
		return (NULL);
	if (!(object = (t_object *)malloc(sizeof(t_object))))
		return (NULL);
	object->sub_object = NULL;
	mat4_init(object->matrix);
	if (!(object->polygons = list2_create()))
	{
		free(object);
		return (NULL);
	}
	tex = libui_surface_image_load_32argb(img, sizex, sizey);
	charge_indices(object->polygons, obj, tex);
	return (object);
}
