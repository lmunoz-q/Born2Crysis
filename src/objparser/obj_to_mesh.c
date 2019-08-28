/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_to_mesh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 17:40:11 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/27 18:19:55 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

static void		load_polygon(t_indice *i, t_polygon *p, t_obj *obj)
{
	SDL_memcpy(p->v01.a, obj->vertices_s[i->v[0] - 1], sizeof(double) * 3);
	p->v01.a[3] = 1;
	SDL_memcpy(p->v12.a, obj->vertices_s[i->v[1] - 1], sizeof(double) * 3);
	p->v12.a[3] = 1;
	SDL_memcpy(p->v20.a, obj->vertices_s[i->v[2] - 1], sizeof(double) * 3);
	p->v20.a[3] = 1;
	if (obj->has_texture)
	{
		SDL_memcpy(p->v01_uv.a, obj->vertices_uv_s[i->uv[0] - 1],
			sizeof(double) * 2);
		SDL_memcpy(p->v12_uv.a, obj->vertices_uv_s[i->uv[1] - 1],
			sizeof(double) * 2);
		SDL_memcpy(p->v20_uv.a, obj->vertices_uv_s[i->uv[2] - 1],
			sizeof(double) * 2);
	}
	else
	{
		p->v01_uv = (t_vec2d){.a = {0, 0}};
		p->v12_uv = (t_vec2d){.a = {0, 0}};
		p->v20_uv = (t_vec2d){.a = {0, 0}};
	}
}

static void		charge_indices(t_mesh *mesh, t_obj *obj, int id)
{
	t_indice	*indice;
	t_node		*head;
	Uint32		i;

	if (!(mesh->polygons = (t_polygon *)SDL_calloc(sizeof(t_polygon),
		obj->indices->size)))
		return ;
	mesh->polygonnum = obj->indices->size;
	head = obj->indices->list;
	i = (Uint32)-1;
	while (++i < mesh->polygonnum)
	{
		indice = head->data;
		load_polygon(indice, &mesh->polygons[i], obj);
		if (indice->tex_id != -1)
			mesh->polygons[i].tex_id = indice->tex_id;
		else
			mesh->polygons[i].tex_id = id;
		mesh->polygons[i].transparency = 0;
		head = head->next;
	}
}

static void		scale_object(t_mesh *m)
{
	double		ratio;
	t_mat4d		scalemat;
	int			i;

	ratio = 5.0 / m->radius;
	mat4_init(&scalemat);
	scalemat = mat4_scale(scalemat, ratio, ratio, ratio);
	i = -1;
	while ((Uint32)++i < m->polygonnum)
	{
		m->polygons[i].v01 = mat4vec4_multiply(scalemat, m->polygons[i].v01);
		m->polygons[i].v12 = mat4vec4_multiply(scalemat, m->polygons[i].v12);
		m->polygons[i].v20 = mat4vec4_multiply(scalemat, m->polygons[i].v20);
	}
}

t_mesh			*obj_to_mesh(t_obj *obj, char *img, t_texture_mode mode)
{
	t_mesh		*mesh;
	int			id;

	if (!obj)
		return (NULL);
	if (!(mesh = (t_mesh *)malloc(sizeof(t_mesh))))
		return (NULL);
	mat4_init(&mesh->matrix);
	mesh->sector_id = -1;
	mesh->polygonnum = 0;
	mesh->walls = NULL;
	mesh->nb_walls = 0;
	id = load_texture_from_bmp(img, mode);
	charge_indices(mesh, obj, id);
	mesh->radius = get_mesh_radius(mesh);
	scale_object(mesh);
	mesh->radius = get_mesh_radius(mesh);
	return (mesh);
}
