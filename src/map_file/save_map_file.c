#include <map_file.h>

t_counter	count_world(t_world *w)
{
	t_counter	out;
	Uint32		i;
	Uint32		j;

	out = (t_counter){w->sectornum, 0, 0, 0, 0, 0, 0, 0};
	i = (Uint32)-1;
	while (++i < w->sectornum)
	{
		out.nb_mesh += w->sectors[i].meshnum;
		out.nb_lights += w->sectors[i].lights.light_count;
		out.nb_entities += w->sectors[i].nb_entities;
		j = (Uint32)-1;
		while (++j < w->sectors[i].meshnum)
		{
			out.nb_polygons += w->sectors[i].mesh[j].polygonnum;
			out.nb_walls += w->sectors[i].mesh[j].nb_walls;
		}
	}
	return (out);
}

Uint8		*write_textures(Uint8 *p, t_texture *tex, Uint32 c)
{
	size_t	size;

	tex = &tex[-1];
	while (c-- && (tex = &tex[1]))
	{
		*(t_map_file_texture*)p = (t_map_file_texture){
			.mode = tex->mode, .size = tex->size};
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

Uint8		*write_entities(Uint8 *p, t_entity *ent, Uint32 c)
{
	ent = &ent[-1];
	while (c-- && (ent = &ent[1]))
	{
		*(t_map_file_entity*)p = (t_map_file_entity){
			.flags = ent->flags,
			.position = ent->position,
			.look = ent->look,
			.velocity = ent->velocity,
			.can_jump = ent->can_jump,
			.can_go_up = ent->can_go_up,
			.can_go_down = ent->can_go_down,
			.radius = ent->radius,
			.height = ent->height};
		p = (Uint8*)&((t_map_file_entity*)p)[1];
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
		*sp = (t_map_file_sector){sec->meshnum, sec->nb_entities,
							sec->lights.light_count, sec->physics};
		p = write_meshes(p, sec->mesh, sec->meshnum);
		p = write_entities(p, sec->entites, sec->nb_entities);
		size = sec->lights.light_count * sizeof(t_light);
		SDL_memcpy(p, sec->lights.lights, size);
		p += size;
	}
	return (p);
}

t_map_file	*world_to_map_file(t_world *w)
{
	t_map_file	*out;
	Uint8		*ptr;
	t_counter	c;
	Uint64		size;

	c = count_world(w);
	size = sizeof(t_map_file) + c.nb_sectors * sizeof(t_map_file_sector)
		+ c.nb_mesh * sizeof(t_map_file_mesh)
		+ c.nb_entities * sizeof(t_map_file_entity)
		+ c.nb_lights * sizeof(t_light)
		+ c.nb_polygons * sizeof(t_polygon)
		+ c.nb_walls * sizeof(t_wall)
		+ c.nb_textures * sizeof(t_map_file_texture)
		+ c.nb_pixels * sizeof(Uint32);
	printf("expected size: %llu\n", size);
	if ((out = SDL_malloc(size)) == NULL)
		return (NULL);
	*out = (t_map_file){size, c.nb_textures, c.nb_sectors, {}};
	ptr = (Uint8*)&out[1];
	ptr = write_meshes(ptr, w->skybox, 1);
	ptr = write_textures(ptr, NULL, 0); //to be fixed
	write_sectors(ptr, w->sectors, w->sectornum);
	return (out);
}
