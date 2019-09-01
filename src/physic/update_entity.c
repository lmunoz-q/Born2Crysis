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

static inline void			friction_clip_effect(t_wall *wall,
							t_eidos_frame *proj, int *collision, t_vec3d cor)
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

static inline int			collision_loop(t_eidos_frame *proj, int mode,
												int collision, t_player *player)
{
	t_vec3d	look;
	t_eidos	*eidos;

	eidos = &player->entity.eidos;
	if (mode)
	{
		look = proj->look;
		if (eidos->eidos_tick > 0)
			*proj = eidos->eidos_save[--eidos->eidos_tick];
		else
			init_player(player, get_world());
		proj->velocity = (t_vec3d){{0, 0, 0}};
		proj->look = look;
	}
	else if (!vec3_eqal(proj->position,
		eidos->eidos_save[eidos->eidos_tick].position))
	{
		if (eidos->eidos_tick == EIDOS_MAX - 1)
			SDL_memmove(eidos->eidos_save, &eidos->eidos_save[1],
				(EIDOS_MAX - 1) * sizeof(t_eidos_frame));
		else
			++eidos->eidos_tick;
		eidos->eidos_save[eidos->eidos_tick - 1] = *proj;
	}
	return (collision);
}

static inline int			update_entity_against_walls(t_eidos_frame *proj,
							t_wall walls[1024], int nb_walls, t_player *player)
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
				if (pass == 1 && vec3_magnitude(cor) > 0.01)
					collision_loop(proj, 1, 1, player);
				if (pass == 1)
					return (1);
				friction_clip_effect(&walls[it], proj, &collision, cor);
			}
		}
	return (collision_loop(proj, 0, collision, player));
}

static inline t_eidos_frame	base_physics(t_eidos_frame e, t_sector_physics sp,
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

int							update_player(t_world *world,
											t_player *player)
{
	t_wall			walls[1024];
	int				nb_wall;
	int				collision;
	t_eidos_frame	*ef;

	if (!world->sectornum)
		return (-1);
	if (player->entity.eidos.rewinding)
		return (eidos_rewind(&player->entity));
	ef = &player->entity.body;
	*ef = base_physics(*ef, ef->sector->physics, world);
	collision = 0;
	if (ef->flags & EF_CLIP || ef->flags & EF_ACTIVATE)
	{
		SDL_memset(walls, 0, sizeof(walls));
		if ((nb_wall = prepare_walls(walls, *ef, ef->sector, world)) > 0)
			collision = update_entity_against_walls(ef, walls, nb_wall, player);
	}
	if (!collision && ef->flags & EF_FRICTION)
		ef->velocity = vec3vec3_multiply(ef->velocity,
			ef->sector->physics.drag);
	return (collision);
}
