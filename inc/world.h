/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:12:06 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/11 00:00:07 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "mflib.h"
# include "libui.h"

typedef t_list2		t_polygonlist;

typedef struct		s_polygon
{
	double			v01_o[4];
	double			v12_o[4];
	double			v20_o[4];
	double			v01[4];
	double			v12[4];
	double			v20[4];
	double			v01_uv[2];
	double			v12_uv[2];
	double			v20_uv[2];
	double			v_light[3];
	SDL_Surface		*texture;
	double			normal_o[4];
	double			normal[4];
	t_bool			active;
	t_bool			preloaded_normal;
	t_bool			is_clipped;
}					t_polygon;

typedef struct		s_surface
{
	t_list2			*polygons;
	int				next_sector_id;
	double			matrix[4][4];
}					t_surface;

typedef struct		s_object
{
	t_list2			*polygons;
	double			matrix[4][4];
	struct s_object	*sub_object;
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
	unsigned int	sectornum;
	t_sector		*sectors;
}					t_world;

t_sector			*get_sector(int id, t_world *world);

#endif
