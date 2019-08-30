/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_crouch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 13:03:10 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 17:22:08 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

int		test_imediate_collision(t_entity *e)
{
	t_wall	walls[1024];
	int		nb_walls;
	t_vec3d	cl[2];
	t_vec3d	v;

	cl[0] = e->position;
	cl[1] = cl[0];
	cl[1].n.y += e->height;
	nb_walls = prepare_walls(walls, *e, e->sector, get_world());
	while (nb_walls--)
		if (collision_capsule_wall(&v, cl, e->radius, walls[nb_walls]))
			return (1);
	return (0);
}

void	kf_crouch(void *param)
{
	t_e		*e;

	e = param;
	if (e->main_player.entity.body.can_go_down)
	{
		if (e->main_player.entity.body.velocity.n.y > -1)
			e->main_player.entity.body.velocity.n.y -= 0.2;
	}
	else
	{
		if (e->main_player.entity.pse == PSE_CROUCH)
		{
			e->main_player.entity.pse = PSE_NORMAL;
			e->main_player.entity.body.height = 8;
			if (test_imediate_collision(&e->main_player.entity.body))
			{
				e->main_player.entity.pse = PSE_CROUCH;
				e->main_player.entity.body.height = 4;
			}
		}
		else
		{
			e->main_player.entity.body.position.n.y += 4;
			e->main_player.entity.pse = PSE_CROUCH;
			e->main_player.entity.body.height = 4;
		}
	}
}
