/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:46:33 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/11 19:46:34 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>
#include <world.h>
#include <stdio.h>

int	update_entity_against_walls(t_entity *proj, t_entity *ent, t_wall walls[64], int nb_walls, t_sector_physics sp)
{
	int			it;
	int			pass;
	double		cor;
	double		y;
	int			collision;

	(void)sp;
	if (nb_walls < 1)
		return (0);
	pass = -1;
	collision = 0;
	while (++pass < 2 && (it = -1))
		while (++it < nb_walls)
		{
			if ((y = entity_wall_collision(*ent, *proj, walls[it], &cor)) != -42)
			{
				if (pass == 1)
				{
					if (cor > 0.001)
					{
						*proj = *ent;
						proj->velocity = (t_vec3d){{0, 0, 0}};
					}
					return (1);
				}
				else
				{
					collision = 1;
					proj->position = vec3vec3_add(proj->position, vec3scalar_multiply(walls[it].normal, cor));
					{
						//recalculate velocity after collision:
						//get the magnitude of the velocity mv:
						//mv = magnitude(velocity)
						//get the dot between the velocity and the normal of the plane:
						//d = velocity . no
						//get the axis of rotation perpendicular to both the velocity and the plane r
						//get the new direction (r cross n) with length mv * d
						// if (cor > 0.001)

							double	mv = vec3_magnitude(proj->velocity);
							if (mv != 0.0)
							{
								t_vec3d	nv = vec3scalar_divide(proj->velocity, mv);
								printf("nv: %f %f %f\n", nv.n.x, nv.n.y, nv.n.z);
								double d = vec3_dot(nv, walls[it].normal);
								// d = 1.0 - fabs(d);
								d += 1.0;
								if (d < walls[it].friction)
									d = walls[it].friction;
								// double d = 1;
								t_vec3d axis = vec3vec3_crossproduct(nv, walls[it].normal);
								printf("velocity 1: %f %f %f\n", proj->velocity.n.x, proj->velocity.n.y, proj->velocity.n.z);
								t_vec3d	t = vec3vec3_crossproduct(walls[it].normal, axis);
								printf("t: %f %f %f\n", t.n.x, t.n.y, t.n.z);
								proj->velocity = vec3scalar_multiply(t, d * mv);
								printf("mv: %f, d: %f, velocity 2: %f %f %f\n", mv, d, proj->velocity.n.x, proj->velocity.n.y, proj->velocity.n.z);
							}
						if (y > 0)
							proj->onground = TRUE;
						// if (y > 0.5) //temporary fix while working on velocity formula
						// 	proj->velocity.n.y = 0;
					}
					/*
					if (type == 1)
					{
						printf("ground contact\n");
						proj->velocity.n.y = 0;
						proj->onground = TRUE;
					}
					if (type == 2)
					{
						printf("ramp contact\n");
						proj->onground = TRUE;
						// proj->velocity.n.y = 0;
					}
					if (type == 4)
					{
						printf("wall contact 1\n");
					}
					if (type == 5)
					{
						printf("wall contact 2\n");
						// if (proj->velocity.n.y > 0.0)
						// 	proj->velocity.n.y = 0.0;
					}
					*/
				}
			}
		}
	return (collision);
}

int	add_mesh(t_mesh *mesh, t_wall walls[64], int *nb_walls, int sectors_ids[16],
	int adjacents_sectors[2], t_entity proj)
{
	int		it;
	t_vec4d	c;
	t_wall	wall;

	if (mesh->sector_id != -1)
	{
		if (adjacents_sectors[0] == 16)
			return (-1);
		it = -1;
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
			wall.friction = mesh->walls[it].friction;
			walls[(*nb_walls)++] = wall;
		}
	}
	return (0);
}

int	prepare_walls(t_wall walls[64], t_entity proj, t_sector *sector,
	t_world *world)
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
			add_mesh(sector->objects[it].mesh, walls, &nb_walls, sector_ids,
				adjacent_sectors, proj);
		it = -1;
		while (++it < sector->meshnum)
			add_mesh(&sector->mesh[it], walls, &nb_walls, sector_ids,
				adjacent_sectors, proj);
	}
	return (nb_walls);
}

t_entity	basic_physics(t_entity e, t_sector_physics sp)
{
	e.position = vec3vec3_add(e.position, e.velocity);
	if (e.flags & EF_GRAVITY)
		e.velocity = vec3vec3_add(e.velocity,
			vec3scalar_multiply(sp.gravity, DELTATIME));
	if (e.flags & EF_FRICTION)
		e.velocity = vec3vec3_multiply(e.velocity, sp.global_friction);
	if (e.velocity.n.x < -sp.speed_limit.n.x)
		e.velocity.n.x = -sp.speed_limit.n.x;
	if (e.velocity.n.x > sp.speed_limit.n.x)
		e.velocity.n.x = sp.speed_limit.n.x;
	if (e.velocity.n.y < -sp.speed_limit.n.y)
		e.velocity.n.y = -sp.speed_limit.n.y;
	if (e.velocity.n.y > sp.speed_limit.n.y)
		e.velocity.n.y = sp.speed_limit.n.y;
	if (e.velocity.n.z < -sp.speed_limit.n.z)
		e.velocity.n.z = -sp.speed_limit.n.z;
	if (e.velocity.n.z > sp.speed_limit.n.z)
		e.velocity.n.z = sp.speed_limit.n.z;
	return (e);
}

int	update_entity(t_world *world, t_entity *ent)
{
	static t_wall	walls[64] = {};
	int				nb_walls;
	t_entity		proj;
	t_sector		*sector;
	int				collision;

	if ((sector = get_sector(ent->sector, world)) == NULL)
		return (0);
	proj = basic_physics(*ent, sector->physics);
	collision = 0;
	if (ent->flags & EF_CLIP)
	{
		SDL_memset(walls, 0, sizeof(walls));
		nb_walls = prepare_walls(walls, proj, sector, world);
		collision = update_entity_against_walls(&proj, ent, walls, nb_walls,
			sector->physics);
	}
	if (!collision)
	{
		//future drag
		proj.velocity = vec3vec3_multiply(proj.velocity, (t_vec3d){{0.90, 1, 0.90}});
	}
	*ent = proj;
	return (0);
}
