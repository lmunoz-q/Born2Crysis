#include <doom-nukem.h>
#include <world.h>
#include <stdio.h>

int	update_entity_against_walls(t_entity *proj, t_entity *ent, t_wall walls[64], int nb_walls)
{
	int			it;
	int			pass;
	double		cor;
	int			type;

	if (nb_walls < 1)
		return (0);
	pass = -1;
	while (++pass < 2 && (it = -1))
		while (++it < nb_walls)
		{
			if ((type = entity_wall_collision(*ent, *proj, walls[it], &cor)))
			{
				if (pass == 1 && cor > 0.01)
				{
					*proj = *ent;
					proj->velocity = (t_vec3d){{0, 0, 0}};
					return (0);
				}
				else
				{
					proj->position = vec3vec3_add(proj->position, vec3scalar_multiply(walls[it].normal, cor));
					if (type == 1)
					{
						// printf("ground contact\n");
						proj->velocity.n.y = 0;
						proj->onground = TRUE;
					}
					if (type == 2)
					{
						proj->onground = TRUE;
						// proj->velocity.n.y = 0;
					}
					if (type == 4)
					{
						// printf("wall contact 1\n");
					}
					if (type == 5)
					{
						// printf("wall contact 2\n");
						// if (proj->velocity.n.y > 0.0)
						// 	proj->velocity.n.y = 0.0;
					}
				}
			}
		}
	return (0);
}

t_entity	basic_physics(t_entity e)
{
	e.position = vec3vec3_add(e.position, e.velocity);
	e.velocity.n.y -= (D_GRAVITY * DELTATIME);
	if (e.velocity.n.y < -3.0)
		e.velocity.n.y = -3.0;
	// printf("y velocity: %f\n", e.velocity.n.y);
	e.velocity.n.x *= DEFAULT_FRICTION;
	e.velocity.n.z *= DEFAULT_FRICTION;
	return (e);
}

int	add_mesh(t_mesh *mesh, t_wall walls[64], int *nb_walls, int sectors_ids[16], int adjacents_sectors[2], t_entity proj)
{
	int		it;
	t_vec4d	c;
	t_wall	wall;

	if (mesh->sector_id != -1)
	{
		if (adjacents_sectors[0] == 16)
			return (-1);
		it = adjacents_sectors[1] - 1;
		while (++it < adjacents_sectors[0])
			if (sectors_ids[it] == mesh->sector_id)
				break ;
		if (it == adjacents_sectors[0])
		{
			++adjacents_sectors[0];
			sectors_ids[it] = mesh->sector_id;
		}
	}
	it = -1;
	while (++it < mesh->nb_walls)
	{
		c = (t_vec4d){.c3 = {.vec3d = mesh->walls[it].center, .w = 1}};
		c.c3.vec3d = vec3vec3_substract(mat4vec4_multiply(mesh->matrix, c).c3.vec3d, proj.position);
		if (c.n.x * c.n.x + c.n.y * c.n.y + c.n.z * c.n.z <= mesh->walls[it].radius * mesh->walls[it].radius)
		{
			wall.normal = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {.vec3d = mesh->walls[it].normal}}).c3.vec3d;
			wall.vertices[0] = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].vertices[0], 1}}).c3.vec3d;
			wall.vertices[1] = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].vertices[1], 1}}).c3.vec3d;
			wall.vertices[2] = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].vertices[2], 1}}).c3.vec3d;
			wall.center = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].center, 1}}).c3.vec3d;
			wall.radius = mesh->walls[it].radius;
			walls[(*nb_walls)++] = wall;
		}
	}
	return (0);
}

int	prepare_walls(t_wall walls[64], t_entity proj, t_sector *sector, t_world *world)
{
	int	nb_walls;
	int	sector_ids[16];
	int	adjacent_sectors[2];
	int	it;

	nb_walls = 0;
	sector_ids[0] = (int)((sector - world->sectors) / sizeof(t_sector));
	adjacent_sectors[0] = 1;
	adjacent_sectors[1] = 0;
	while (adjacent_sectors[1] < adjacent_sectors[0])
	{
		sector = &world->sectors[sector_ids[adjacent_sectors[1]++]];
		it = -1;
		while (++it < sector->objectnum)
			add_mesh(sector->objects[it].mesh, walls, &nb_walls, sector_ids, adjacent_sectors, proj);
		it = -1;
		while (++it < sector->meshnum)
			add_mesh(&sector->mesh[it], walls, &nb_walls, sector_ids, adjacent_sectors, proj);
	}
	return (nb_walls);
}

int	update_entity(t_world *world, t_entity *ent)
{
	static t_wall	*walls;
	int				nb_walls;
	t_entity		proj;
	t_sector		*sector;
	t_vec3d			or;

	if ((sector = get_sector(ent->sector, world)) == NULL)
		return (0);
	walls = (t_wall[64]){};
	proj = basic_physics(*ent);
	nb_walls = prepare_walls(walls, proj, sector, world);
	or = proj.position;
	update_entity_against_walls(&proj, ent, walls, nb_walls);
	*ent = proj;
	return (proj.position.n.x != or.n.x || proj.position.n.y != or.n.y || proj.position.n.z != or.n.z);
}
