/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:12:06 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/01 18:05:51 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "mflib.h"
# include "libui.h"

typedef t_list2		t_polygonlist;

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

typedef struct		s_surface
{
	t_polygon		*polygons_o;
	int				polygon_num;
	int				next_sector_id;
	double			matrix[4][4];
}					t_surface;

typedef struct		s_object
{
	t_list2			*polygons;
	double			matrix[4][4];
	struct s_object	*sub_object;
	int				sub_object_num;
}					t_object;

typedef struct		s_sector
{
	int				id;
	int				surfacenum;
	int				objectnum;
	t_surface		*surfaces;
	t_object		*objects;
}					t_sector;

typedef struct		s_world
{
	t_polygon		*p_buff;
	unsigned int	sectornum;
	t_sector		*sectors;
}					t_world;

t_sector			*get_sector(int id, t_world *world);
t_polygon			*polygon_copy(t_polygon *p);

#endif
