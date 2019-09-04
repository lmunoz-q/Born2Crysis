/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 22:43:24 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/31 22:43:26 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map_file.h>

Uint8		*write_textures(Uint8 *p, t_texture *tex, Uint32 c)
{
	size_t	size;

	tex = &tex[-1];
	while (c-- && (tex = &tex[1]))
	{
		*(t_map_file_texture*)p = (t_map_file_texture){
			.mode = tex->mode, .size = tex->size, .id = tex->id};
		SDL_memcpy(((t_map_file_texture*)p)->path, tex->path,
			sizeof(tex->path));
		p = (Uint8*)&((t_map_file_texture*)p)[1];
		size = tex->size.n.x * tex->size.n.y * sizeof(Uint32);
		SDL_memcpy(p, tex->texture->pixels, size);
		p += size;
	}
	return (p);
}

Uint8		*write_meshes(Uint8 *p, t_mesh *mesh, Uint32 c)
{
	size_t	size;

	mesh = &mesh[-1];
	while (c-- && (mesh = &mesh[1]))
	{
		*(t_map_file_mesh*)p = (t_map_file_mesh){
			.nb_polygons = mesh->polygonnum,
			.matrix = mesh->matrix,
			.sector_id = mesh->sector_id,
			.portal_normal = mesh->portal_normal,
			.radius = mesh->radius,
			.nb_walls = mesh->nb_walls};
		p = (Uint8*)&((t_map_file_mesh*)p)[1];
		size = mesh->polygonnum * sizeof(t_polygon);
		SDL_memcpy(p, mesh->polygons, size);
		p += size;
		size = mesh->nb_walls * sizeof(t_wall);
		SDL_memcpy(p, mesh->walls, size);
		p += size;
	}
	return (p);
}

Uint8		*write_sectors(Uint8 *p, t_sector *sec, Uint32 c)
{
	t_map_file_sector	*sp;
	size_t				size;

	sec = &sec[-1];
	while (c-- && (sec = &sec[1]))
	{
		sp = (t_map_file_sector*)p;
		p = (Uint8*)&sp[1];
		*sp = (t_map_file_sector){.nb_mesh = sec->meshnum,
			.nb_lights = sec->lights.light_count,
			.id = sec->id,
			.physics = sec->physics};
		p = write_meshes(p, sec->mesh, sec->meshnum);
		size = sec->lights.light_count * sizeof(t_light);
		SDL_memcpy(p, sec->lights.lights, size);
		p += size;
	}
	return (p);
}

Uint8		*write_lib(Uint8 *ptr, t_library lib)
{
	uint64_t	i;
	uint64_t	j;

	i = (uint64_t)-1;
	while (++i < lib.nb_functions)
	{
		mf_strncpy((char*)ptr, lib.function_name[i], 12);
		ptr += 12;
		mf_memcpy(ptr, &lib.function[i], 24);
		ptr += 24;
		mf_memcpy(ptr, lib.function[i].code, lib.function[i].code_size);
		ptr += lib.function[i].code_size;
		j = (uint64_t)-1;
		while (++j < lib.function[i].alias_size)
			*ptr++ = lib.function[i].alias_memory[j].type;
		j = (uint64_t)-1;
		while (++j < lib.function[i].needed_symbols)
		{
			mf_strncpy((char*)ptr, lib.function[i].symbols[j].name, 12);
			ptr += 12;
		}
	}
	return (ptr);
}

t_map_file	*world_to_map_file(t_world *w)
{
	t_map_file	*out;
	Uint8		*ptr;
	t_counter	c;
	Uint64		size;

	c = count_world(w);
	size = sizeof(t_map_file) + c.nb_sectors * sizeof(t_map_file_sector)
		+ (c.nb_mesh + (w->skybox != NULL)) * sizeof(t_map_file_mesh)
		+ c.nb_lights * sizeof(t_light) + (c.nb_polygons + (w->skybox != NULL
		? w->skybox->polygonnum : 0)) * sizeof(t_polygon)
		+ c.nb_walls * sizeof(t_wall) + c.nb_pixels * sizeof(Uint32)
		+ c.nb_textures * sizeof(t_map_file_texture)
		+ c.nb_functions * sizeof(t_map_file_function)
		+ c.nb_code * sizeof(char) + c.nb_alias * sizeof(t_ptr_type)
		+ c.nb_symbols * sizeof(char[12]);
	if ((out = SDL_malloc(size)) == NULL)
		return (NULL);
	*out = (t_map_file){.total_size = size, .nb_textures = c.nb_textures,
		.nb_sectors = c.nb_sectors, .spawn_point = w->goal_point,
		.nb_functions = c.nb_functions};
	ptr = (Uint8*)&out[1];
	ptr = write_meshes(ptr, w->skybox, 1);
	ptr = write_textures(ptr, w->textures, c.nb_textures);
	write_lib(write_sectors(ptr, w->sectors, w->sectornum), w->lib);
	return (out);
}
