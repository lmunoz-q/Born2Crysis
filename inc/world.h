/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:12:06 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/04 23:16:32 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "mflib.h"
# include "libui.h"
# include <stdlib.h>

typedef struct		s_polygon
{
	double			v01[4];
	double			v12[4];
	double			v20[4];
	double			normal[4];
	double			v01_uv[2];
	double			v12_uv[2];
	double			v20_uv[2];
	double			v_light[3];
	int				tex_id;
	
}					t_polygon;

typedef struct		s_object
{
	t_polygon		*polygons;
	double			matrix[4][4];
	struct s_object	*sub_object;
	int				sub_object_num;
	int				polygonnum;
	int				index;
}					t_object;

typedef struct		s_sector
{
	int				id;
	int				objectnum;
	int				polygonnum;
	int				index;
	t_object		*objects;
	t_polygon		*polygons;
}					t_sector;

typedef struct		s_world
{
	t_polygon		*p_buff;
	int				sectornum;
	t_sector		*sectors;
}					t_world;

t_sector			*get_sector(int id, t_world *world);
t_polygon			*polygon_copy(t_polygon *p);
t_polygon			*get_buffer(t_world *world);
t_bool				init_world(t_world *world);

#endif
