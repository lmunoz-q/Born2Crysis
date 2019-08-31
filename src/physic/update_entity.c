/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2000/00/00 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>
#include <world.h>

static inline void		friction_clip_effect(t_wall *wall, t_entity *proj,
											int *collision, t_vec3d cor)
{
	double	mv;
	double	d;
	t_vec3d	axis;
	t_vec3d	dir;
	t_vec3d	nv;

	if (!*collision && proj->flags & EF_FRICTION)
	{
		mv = vec3_magnitude(proj->velocity);
		if (mv != 0.0)
		{
			nv = vec3scalar_divide(proj->velocity, mv);
			d = 1.0 - fabs(vec3_dot(nv, wall->normal));
			if (d < wall->friction)
				d = wall->friction;
			axis = vec3vec3_crossproduct(nv, wall->normal);
			dir = vec3vec3_crossproduct(wall->normal, axis);
			proj->velocity = vec3scalar_multiply(dir, d * mv);
		}
	}
	*collision = 1;
	if (proj->flags & EF_CLIP)
		proj->position = vec3vec3_add(proj->position, cor);
	if (wall->on_contact_trigger != EFF_NOTHING)
		apply_effect(proj, get_world(), wall->on_contact_trigger);
}

static inline int		update_entity_against_walls(t_entity *proj,
								t_entity *ent, t_wall walls[1024], int nb_walls)
{
	int				it;
	int				pass;
	t_vec3d			cor;
	int				collision;
	t_vec3d			cl[2];

	pass = -1;
	collision = 0;
	while (++pass < 2 - !(proj->flags & EF_CLIP) && (it = -1))
		while (++it < nb_walls)
		{
			cl[0] = proj->position;
			cl[1] = cl[0];
			cl[1].n.y += proj->height;
			if (collision_capsule_wall(&cor, cl, proj->radius, walls[it]))
			{
				if (pass == 1 && vec3_magnitude(cor) > 0.01
						&& !(proj->velocity = (t_vec3d){{0, 0, 0}}).n.x)
					*proj = *ent;
				if (pass == 1)
					return (1);
				friction_clip_effect(&walls[it], proj, &collision, cor);
			}
		}
	return (collision);
}

static inline t_entity	base_physics(t_entity e, t_sector_physics sp,
									t_world *world)
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

int						update_entity(t_world *world, t_entity *ent)
{
	t_wall			walls[1024];
	int				nb_wall;
	t_entity		proj;
	int				collision;

	if (!world->sectornum)
		return (-1);
	proj = base_physics(*ent, ent->sector->physics, world);
	collision = 0;
	if (proj.flags & EF_CLIP || proj.flags & EF_ACTIVATE)
	{
		SDL_memset(walls, 0, sizeof(walls));
		if ((nb_wall = prepare_walls(walls, proj, proj.sector, world)) > 0)
			collision = update_entity_against_walls(&proj, ent, walls, nb_wall);
	}
	if (!collision && proj.flags & EF_FRICTION)
		proj.velocity = vec3vec3_multiply(proj.velocity,
			proj.sector->physics.drag);
	*ent = proj;
	return (collision);
}
