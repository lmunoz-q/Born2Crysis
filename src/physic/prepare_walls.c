/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2000/00/00 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <physic.h>
#include <world.h>

static inline void	add_mesh_1(t_mesh *mesh, t_wall walls[1024],
								t_add_mesh *am, t_eidos_frame proj)
{
	int32_t	it;
	t_vec4d	c;

	it = (int32_t)-1;
	while (++it < mesh->nb_walls)
	{
		c = (t_vec4d){.c3 = {.vec3d = mesh->walls[it].center, .w = 1}};
		c.c3.vec3d = vec3vec3_substract(c.c3.vec3d, proj.position);
		if (c.n.x * c.n.x + c.n.y * c.n.y + c.n.z * c.n.z
			<= mesh->walls[it].radius * mesh->walls[it].radius
			&& !isnan(vec3_dot(mesh->walls[it].normal, (t_vec3d){{0, 0, 0}})))
			walls[am->nb_walls++] = mesh->walls[it];
	}
}

static inline void	add_mesh_0(t_mesh *mesh, t_wall walls[1024],
								t_add_mesh *am, t_eidos_frame proj)
{
	int32_t	it;

	if (mesh->sector_id != (int32_t)-1)
	{
		it = (int32_t)-1;
		while (++it < am->adjacent_sectors[0])
			if (am->sector_ids[it] == mesh->sector_id)
				break ;
		if (it == am->adjacent_sectors[0])
		{
			if (am->adjacent_sectors[0] == 16)
				return ;
			++am->adjacent_sectors[0];
			am->sector_ids[it] = mesh->sector_id;
		}
	}
	add_mesh_1(mesh, walls, am, proj);
}

int					prepare_walls(t_wall walls[1024], t_eidos_frame proj,
									t_sector *sector, t_world *world)
{
	int32_t		it;
	t_add_mesh	am;

	am = (t_add_mesh){0, {0}, {0}};
	am.sector_ids[0] = (int32_t)((sector - world->sectors) / sizeof(t_sector));
	am.adjacent_sectors[0] = 1;
	am.adjacent_sectors[1] = 0;
	while (am.adjacent_sectors[1] < am.adjacent_sectors[0])
	{
		sector = &world->sectors[am.sector_ids[am.adjacent_sectors[1]++]];
		it = (int32_t)-1;
		while (++it < sector->meshnum)
			add_mesh_0(&sector->mesh[it], walls, &am, proj);
	}
	return (am.nb_walls);
}
