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
	Uint32				it;

	it = (Uint32)-1;
	while (++it < c)
	{
		sp = (t_map_file_sector*)p;
		p = (Uint8*)&sp[1];
		buf[it] = (t_sector){.lights = {.light_count = sp->nb_lights,
				.lights = SDL_malloc(sizeof(t_light) * sp->nb_lights)},
			.nb_entities = sp->nb_entities, .entites = SDL_malloc(
				sizeof(t_entity) * sp->nb_entities),
			.meshnum = sp->nb_mesh, .mesh = SDL_malloc(
				sizeof(t_mesh) * sp->nb_mesh),
			.physics = sp->physics, .id = it};
		if ((buf[it].lights.light_count && buf[it].lights.lights == NULL)
				|| (buf[it].nb_entities && buf[it].entites == NULL)
				|| (buf[it].meshnum && buf[it].mesh == NULL)
				|| (p = load_meshes(p, buf[it].mesh, sp->nb_mesh)) == NULL)
			return (NULL);
		p = load_entities(p, buf[it].entites, sp->nb_entities, &buf[it]);
		SDL_memcpy(buf[it].lights.lights, p, sp->nb_lights * sizeof(t_light));
		p += sp->nb_lights * sizeof(t_light);
	}
	return (p);
}

Uint8	*load_textures(Uint8 *p, t_mesh *buf, Uint32 c)
{
	(void)buf;
	(void)c;
	return (p);
}

t_world	map_file_to_world(t_map_file *stream)
{
	Uint8	*p;
	t_world	out;

	out = (t_world){.sectornum = stream->nb_sectors};
	p = (Uint8*)&stream[1];
	if ((out.skybox = SDL_malloc(sizeof(t_mesh))) == NULL
		|| ((p = load_meshes(p, out.skybox, 1)) == NULL)
		|| ((p = load_textures(p, /*out.textures*/NULL, stream->nb_textures)) == NULL)
		|| load_sectors(p, out.sectors, out.sectornum) == NULL)
		return ((t_world){});
	return (out);
}
