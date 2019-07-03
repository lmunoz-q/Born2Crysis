/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:12:06 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/03 16:21:12 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include <stdlib.h>

# include "mflib.h"
# include "libui.h"

# include "lights.h"

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
}					t_polygon;

typedef struct		s_mesh
{
	t_polygon		*polygons;
	double			matrix[4][4];
	int				polygonnum;
	int				sector_id;
	double			portal_normal[3];
	double			radius;
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
}					t_sector;

typedef struct		s_world
{
	t_sector		*sectors;
	int				sectornum;
	
}					t_world;

t_bool				init_world(t_world *world);
t_world				*set_world(t_world *world);
t_world				*get_world();
void				init_portals(t_world *world);
t_polygon			*set_polygon_buffer(t_polygon *addr);
t_polygon			*get_polygon_buffer();
t_polygon			*polygon_copy(t_polygon *p);
t_sector			*get_sector(int id, t_world *world);
t_polygon			*load_buffer(t_world *world);
double				get_mesh_radius(t_mesh *mesh);

#endif
