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
	{
		while (++it < nb_walls)
		{
			cl[0] = proj->position;
			cl[1] = cl[0];
			cl[1].n.y += proj->height;
			if (collision_capsule_wall(&cor, cl, proj->radius, walls[it]))
			{
				if (pass == 1)
				{
					printf("PAF 1\n");
					if (vec3_magnitude(cor) > 0.0001)
					{
						*proj = *ent;
						proj->velocity = (t_vec3d){{0, 0, 0}};
					}
					return (1);
				}
				else
				{
					collision = 1;
					if (proj->flags & EF_CLIP)
						proj->position = vec3vec3_add(proj->position, cor);
					if (proj->flags & EF_FRICTION)
					{
						double mv = vec3_magnitude(proj->velocity);
						if (mv != 0.0)
						{
							t_vec3d nv = vec3scalar_divide(proj->velocity, mv);
							double  d;
							d = vec3_dot(nv, walls[it].normal);
							d = 1.0 - fabs(d);
							if (d < walls[it].friction)
								d = walls[it].friction;
							t_vec3d axis = vec3vec3_crossproduct(nv, walls[it].normal);
							t_vec3d t = vec3vec3_crossproduct(walls[it].normal, axis);
							proj->velocity = vec3scalar_multiply(t, d * mv);
						}
					}
					if (walls[it].on_contact_trigger != EFF_NOTHING)
						apply_effect(proj, get_world(), walls[it].on_contact_trigger);
				}
			}
		}
	}
	return (collision);
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

int	update_entity(t_world *world, t_entity *ent)
{
	static t_wall	walls[1024] = {};
	int				nb_walls;
	t_entity		proj;
	int				collision;

	if (!world->sectornum)
		return (-1);
	proj = base_physics(*ent, ent->sector->physics, world);
	collision = 0;
	if (proj.flags & EF_CLIP || proj.flags & EF_ACTIVATE)
	{
		SDL_memset(walls, 0, sizeof(walls));
		nb_walls = prepare_walls(walls, proj, proj.sector, world);
		collision = update_entity_against_walls(&proj, ent, walls, nb_walls);
	}
	if (!collision && proj.flags & EF_FRICTION)
		proj.velocity = vec3vec3_multiply(proj.velocity, proj.sector->physics.drag);
	*ent = proj;
	return (collision);
}
