/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:12:06 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/14 12:58:44 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include <stdlib.h>

# include <physic.h>

# include "mflib.h"
# include "libui.h"

# include "lights.h"

# define	MAX_PORTALS_PER_SECTOR	100
# define	D_GRAVITY				0.98

typedef struct		s_polygon
{
	double			v01[4];
	double			v12[4];
	double			v20[4];
	double			normal[3];
	double			v01_uv[2];
	double			v12_uv[2];
	double			v20_uv[2];
	double			v_light[3];
	int				tex_id;
	int				transparency;
}					t_polygon;

typedef struct		s_mesh
{
	t_polygon		*polygons;
	double			matrix[4][4];
	int				polygonnum;
	int				sector_id;
	double			portal_normal[3];
	double			radius;
	t_bool			active;
	int				nb_walls;
	t_wall			*walls;
}					t_mesh;

typedef struct		s_object
{
	t_mesh			*mesh;
	struct s_object	*sub_object;
	int				sub_object_num;
	int				meshnum;
}					t_object;

typedef struct		s_sector
{
	int				id;
	int				objectnum;
	t_object		*objects;
	t_mesh			*mesh;
	t_light_comp	lights;
	int				meshnum;
	t_mesh			*src_portal;
	int				nb_entities;
	t_entity		*entites;
}					t_sector;

typedef struct		s_world
{
	t_sector		*sectors;
	int				sectornum;
	double			gravity;
}					t_world;

t_wall				polygon_to_wall(t_polygon poly);
t_polygon			wall_to_polygon(t_wall wall, int tex_id);

int					update_entity(t_world *world, t_entity *ent);

t_bool				init_world(t_world *world);
t_world				*set_world(t_world *world);
t_world				*get_world();
void				init_portals(t_world *world);
void				gen_portal_outline(t_mesh *m);
t_polygon			*set_polygon_buffer(t_polygon *addr);
t_polygon			*get_polygon_buffer();
t_polygon			*polygon_copy(t_polygon *p);
t_sector			*get_sector(int id, t_world *world);
t_polygon			*load_buffer(t_world *world);
double				get_mesh_radius(t_mesh *mesh);

#endif
