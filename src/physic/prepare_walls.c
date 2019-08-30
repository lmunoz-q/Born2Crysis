#include <physic.h>
#include <world.h>

static inline int	add_mesh(t_mesh *mesh, t_wall walls[1024], int *nb_walls, int32_t sectors_ids[16],
				int32_t adjacents_sectors[2], t_entity proj)
{
	int32_t	it;
	t_vec4d	c;
	t_wall	wall;

	if (mesh->sector_id != (int32_t)-1)
	{
		if (adjacents_sectors[0] == 16)
			return (-1);
		it = (int32_t)-1;
		while (++it < adjacents_sectors[0])
			if (sectors_ids[it] == mesh->sector_id)
				break ;
		if (it == adjacents_sectors[0])
		{
			++adjacents_sectors[0];
			sectors_ids[it] = mesh->sector_id;
		}
	}
	it = (int32_t)-1;
	while (++it < mesh->nb_walls)
	{
		c = (t_vec4d){.c3 = {.vec3d = mesh->walls[it].center, .w = 1}};
		c.c3.vec3d = vec3vec3_substract(c.c3.vec3d, proj.position);
		if (c.n.x * c.n.x + c.n.y * c.n.y + c.n.z * c.n.z <= mesh->walls[it].radius * mesh->walls[it].radius)
		{
			if (isnan(vec3_dot(mesh->walls[it].normal, (t_vec3d){})))
				continue ;
			wall = mesh->walls[it];
			wall.vertices[0] = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].vertices[0], 1}}).c3.vec3d;
			wall.vertices[1] = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].vertices[1], 1}}).c3.vec3d;
			wall.vertices[2] = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].vertices[2], 1}}).c3.vec3d;
			walls[(*nb_walls)++] = wall;
		}
	}
	return (0);
}

int	prepare_walls(t_wall walls[1024], t_entity proj, t_sector *sector,
					 t_world *world)
{
	int		nb_walls;
	int32_t	sector_ids[16];
	int32_t	adjacent_sectors[2];
	int32_t	it;

	nb_walls = 0;
	sector_ids[0] = (int32_t)((sector - world->sectors) / sizeof(t_sector));
	adjacent_sectors[0] = 1;
	adjacent_sectors[1] = 0;
	while (adjacent_sectors[1] < adjacent_sectors[0])
	{
		sector = &world->sectors[sector_ids[adjacent_sectors[1]++]];
		it = (int32_t)-1;
		while (++it < sector->meshnum)
			add_mesh(&sector->mesh[it], walls, &nb_walls, sector_ids,
					 adjacent_sectors, proj);
	}
	return (nb_walls);
}
