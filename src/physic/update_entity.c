/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:46:33 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/29 21:02:46 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>
#include <world.h>
#include <stdio.h>
#include <bodies.h>

int	update_entity_against_walls(t_entity *proj, t_entity *ent, t_wall walls[1024], int nb_walls)
{
	int				it;
	int				pass;
	t_vec3d			cor;
	int				collision;
	t_vec3d			cl[2];

	(void)ent;
	if (nb_walls < 1)
		return (0);
	pass = -1;
	collision = 0;
	while (++pass < 2 - !(proj->flags & EF_CLIP) && (it = -1))
		while (++it < nb_walls)
		{
			cl[0] = proj->position;
			cl[1] = cl[0];
			cl[1].n.y += proj->height;
//			cl[1] = ent->position;
			if (collision_capsule_wall(&cor, cl, proj->radius, walls[it]))
			{
				//printf("cor: %f %f %f\n", cor.n.x, cor.n.y, cor.n.z);
				if (pass == 1)
				{
//					double	test = vec3_magnitude(cor);
					if (vec3_magnitude(cor) > 0.0001)
					{
//						printf("rentered object: %d with force: %f\n", it, test);
//						*proj = *ent;
//						proj->velocity = (t_vec3d){{0, 0, 0}};
					}
					return (1);
				}
				else
				{
					collision = 1;
					if (proj->flags & EF_CLIP)
					{
						proj->position = vec3vec3_add(proj->position, cor);
					}
					if (proj->flags & EF_FRICTION)
					{
						double mv = vec3_magnitude(proj->velocity);
						if (mv != 0.0)
						{
							t_vec3d nv = vec3scalar_divide(proj->velocity, mv);
							double d = vec3_dot(nv, walls[it].normal);
							d = 1.0 - fabs(d);
							if (d < walls[it].friction)
								d = walls[it].friction;
							t_vec3d axis = vec3vec3_crossproduct(nv, walls[it].normal);
							t_vec3d t = vec3vec3_crossproduct(walls[it].normal, axis);
							proj->velocity = vec3scalar_multiply(t, d * mv);
							//proj->velocity = vec3vec3_add(proj->velocity, vec3scalar_multiply(proj->sector->physics.gravity, DELTATIME));
						}
					}
					if (walls[it].on_contact_trigger != EFF_NOTHING)
						apply_effect(proj, get_world(), walls[it].on_contact_trigger);
				}
			}
		}
	return (collision);
}

int	add_mesh(t_mesh *mesh, t_wall walls[1024], int *nb_walls, int32_t sectors_ids[16],
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
		c.c3.vec3d = vec3vec3_substract(/*mat4vec4_multiply(mesh->matrix, c)*/c.c3.vec3d, proj.position);
		if (c.n.x * c.n.x + c.n.y * c.n.y + c.n.z * c.n.z <= mesh->walls[it].radius * mesh->walls[it].radius)
		{
			if (isnan(vec3_dot(mesh->walls[it].normal, (t_vec3d){})))
				continue ;
			wall = mesh->walls[it];
			//wall.normal = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {.vec3d = mesh->walls[it].normal}}).c3.vec3d;
			wall.vertices[0] = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].vertices[0], 1}}).c3.vec3d;
			wall.vertices[1] = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].vertices[1], 1}}).c3.vec3d;
			wall.vertices[2] = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].vertices[2], 1}}).c3.vec3d;
			//wall.center = mat4vec4_multiply(mesh->matrix, (t_vec4d){.c3 = {mesh->walls[it].center, 1}}).c3.vec3d;
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

t_entity	base_physics(t_entity e, t_sector_physics sp, t_world *world)
{
	e.position = vec3vec3_add(e.position, e.velocity);
	if (e.flags & EF_GRAVITY)
		e.velocity = vec3vec3_add(e.velocity,
			vec3scalar_multiply(sp.gravity, DELTATIME));
	if (e.flags & EF_FRICTION)
		e.velocity = vec3vec3_multiply(e.velocity, sp.global_friction);
	if (sp.frame_effect != EFF_NOTHING)
		apply_effect(&e, world, sp.frame_effect);
	return (e);
}

/*
** prepare the vertices of the entity (for now a box with no rotation)
*/
void	entity_mesh(t_entity *e)
{
	e->vertices[0] = (t_vec3d){{e->position.n.x - e->radius, e->position.n.y, e->position.n.z - e->radius}};
	e->vertices[1] = (t_vec3d){{e->position.n.x + e->radius, e->position.n.y, e->position.n.z - e->radius}};
	e->vertices[2] = (t_vec3d){{e->position.n.x + e->radius, e->position.n.y, e->position.n.z + e->radius}};
	e->vertices[3] = (t_vec3d){{e->position.n.x - e->radius, e->position.n.y, e->position.n.z + e->radius}};
	e->vertices[4] = (t_vec3d){{e->position.n.x - e->radius, e->position.n.y + e->height, e->position.n.z - e->radius}};
	e->vertices[5] = (t_vec3d){{e->position.n.x + e->radius, e->position.n.y + e->height, e->position.n.z - e->radius}};
	e->vertices[6] = (t_vec3d){{e->position.n.x + e->radius, e->position.n.y + e->height, e->position.n.z + e->radius}};
	e->vertices[7] = (t_vec3d){{e->position.n.x - e->radius, e->position.n.y + e->height, e->position.n.z + e->radius}};
//	for (int i = 0; i < 8; ++i)
//		printf("v(%d): %f %f %f\n", i, e->vertices[i].n.x, e->vertices[i].n.y, e->vertices[i].n.z);
}

int	update_entity(t_world *world, t_entity *ent)
{
	static t_wall	walls[1024] = {};
	int				nb_walls;
	t_entity		proj;
	int				collision;

	if (!world->sectornum)
		return (-1);
	proj = base_physics(*ent, ent->sector->physics, world);
//	entity_mesh(ent);
	entity_mesh(&proj);
	collision = 0;
	if (proj.flags & EF_CLIP || proj.flags & EF_ACTIVATE)
	{
		SDL_memset(walls, 0, sizeof(walls));
		nb_walls = prepare_walls(walls, proj, proj.sector, world);
		collision = update_entity_against_walls(&proj, ent, walls, nb_walls);
	}
	if (!collision && proj.flags & EF_FRICTION)
	{
		//drag
		proj.velocity = vec3vec3_multiply(proj.velocity, proj.sector->physics.drag);
	}
	*ent = proj;
	return (collision);
}
