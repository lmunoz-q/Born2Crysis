#include <map_file.h>

Uint8	*load_meshes(Uint8 *p, t_mesh *buf, Uint32 c)
{
	t_map_file_mesh	*fm;

	buf = &buf[-1];
	while (c-- && (buf = &buf[1]))
	{
		fm = (t_map_file_mesh*)p;
		*buf = (t_mesh){
			.polygonnum = fm->nb_polygons,
			.polygons = SDL_malloc(sizeof(t_polygon) * fm->nb_polygons),
			.matrix = fm->matrix, .sector_id = fm->sector_id,
			.portal_normal = fm->portal_normal, .radius = fm->radius,
			.nb_walls = fm->nb_walls,
			.walls = SDL_malloc(sizeof(t_wall) * fm->nb_walls)};
		if ((buf->polygonnum && buf->polygons == NULL)
				|| (buf->nb_walls && buf->walls == NULL))
			return (NULL);
		p = (Uint8*)&fm[1];
		SDL_memcpy(buf->polygons, p, sizeof(t_polygon) * buf->polygonnum);
		p += sizeof(t_polygon) * buf->polygonnum;
		SDL_memcpy(buf->walls, p, sizeof(t_wall) * buf->nb_walls);
		p += sizeof(t_wall) * buf->nb_walls;
	}
	return (p);
}

Uint8	*load_entities(Uint8 *p, t_entity *buf, Uint32 c, t_sector *sect)
{
	t_map_file_entity	*fe;

	buf = &buf[-1];
	while (c-- && (buf = &buf[1]))
	{
		fe = (t_map_file_entity*)p;
		*buf = (t_entity){.flags = fe->flags, .position = fe->position,
			.look = fe->look, .velocity = fe->velocity,
			.can_jump = fe->can_jump, .can_go_up = fe->can_go_up,
			.can_go_down = fe->can_go_down, .radius = fe->radius,
			.height = fe->height, .sector = sect, .entities_overlap = {},
			.wall_contacts = {}};
		p = (Uint8*)&fe[1];
	}
	return (p);
}

Uint8	*load_sectors(Uint8 *p, t_sector *buf, Uint32 c)
{
	t_map_file_sector	*sp;

	buf = &buf[-1];
	while (c-- && (buf = &buf[1]))
	{
		sp = (t_map_file_sector*)p;
		p = (Uint8*)&sp[1];
		*buf = (t_sector){.lights = {.light_count = sp->nb_lights,
				.lights = SDL_malloc(sizeof(t_light) * sp->nb_lights)},
			.nb_entities = sp->nb_entities, .entites = SDL_malloc(
				sizeof(t_entity) * sp->nb_entities),
			.meshnum = sp->nb_mesh, .mesh = SDL_malloc(
				sizeof(t_mesh) * sp->nb_mesh),
			.physics = sp->physics, .id = sp->id};
		if ((buf->lights.light_count && buf->lights.lights == NULL)
				|| (buf->nb_entities && buf->entites == NULL)
				|| (buf->meshnum && buf->mesh == NULL)
				|| (p = load_meshes(p, buf->mesh, sp->nb_mesh)) == NULL)
			return (NULL);
		p = load_entities(p, buf->entites, sp->nb_entities, buf);
		SDL_memcpy(buf->lights.lights, p, sp->nb_lights * sizeof(t_light));
		p += sp->nb_lights * sizeof(t_light);
	}
	return (p);
}

Uint8	*load_textures(Uint8 *p, t_texture *buf, Uint32 c)
{
	t_map_file_texture	*ft;

	buf = &buf[-1];
	while (c-- && (buf = &buf[1]))
	{
		ft = (t_map_file_texture*)p;
		*buf = (t_texture){.size = ft->size, .id = ft->id, .mode = ft->mode,
			.texture = SDL_CreateRGBSurface(SDL_SWSURFACE, ft->size.n.x,
				ft->size.n.y, 32, 0xFF0000, 0xFF00, 0xFF, 0xFF000000)};
		if (buf->texture == NULL)
			return (NULL);
		SDL_memcpy(buf->path, ((t_map_file_texture*)p)->path, sizeof(buf->path));
		p = (Uint8*)&ft[1];
		SDL_memcpy(buf->texture->pixels, p,
			buf->size.n.x * buf->size.n.y * sizeof(Uint32));
		p += buf->size.n.x * buf->size.n.y * sizeof(Uint32);
	}
	return (p);
}

t_world	map_file_to_world(t_map_file *stream)
{
	Uint8	*p;
	t_world	out;

	out = (t_world){.sectornum = stream->nb_sectors,
		.spawn_point = stream->spawn_point, .nb_textures = stream->nb_textures};
	p = (Uint8*)&stream[1];
	if ((out.skybox = SDL_malloc(sizeof(t_mesh))) == NULL
		|| (out.textures = SDL_malloc(sizeof(t_texture) * out.nb_textures)) == NULL
		|| (out.sectors = SDL_malloc(sizeof(t_sector) * out.sectornum)) == NULL
		|| ((p = load_meshes(p, out.skybox, 1)) == NULL)
		|| ((p = load_textures(p, out.textures, stream->nb_textures)) == NULL)
		|| load_sectors(p, out.sectors, out.sectornum) == NULL)
		return ((t_world){});
	return (out);
}
