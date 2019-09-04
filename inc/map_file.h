/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2000/00/00 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_FILE_H
# define MAP_FILE_H

# include <world.h>

typedef struct	s_map_file_texture
{
	Uint32		mode;
	Uint32		id;
	t_vec2i		size;
	char		path[1024];
	Uint32		data[0];
}				t_map_file_texture;

typedef struct	s_map_file_entity
{
	Uint32		flags;
	t_vec3d		position;
	t_vec3d		look;
	t_vec3d		velocity;
	Uint32		can_jump : 1;
	Uint32		can_go_up : 1;
	Uint32		can_go_down : 1;
	double		radius;
	double		height;
}				t_map_file_entity;

typedef struct	s_map_file_mesh
{
	Uint32		nb_polygons;
	t_mat4d		matrix;
	Uint32		sector_id;
	t_vec3d		portal_normal;
	double		radius;
	Uint32		nb_walls;
}				t_map_file_mesh;

typedef struct	s_map_file_sector
{
	Uint32				nb_mesh;
	Uint32				nb_entities;
	Uint32				nb_lights;
	Uint32				id;
	t_sector_physics	physics;
}				t_map_file_sector;

typedef struct	s_map_file
{
	Uint64		total_size;
	Uint32		nb_textures;
	Uint32		nb_sectors;
	t_vec3d		spawn_point;
	Uint8		data[0];
}				t_map_file;

typedef struct	s_counter
{
	Uint32	nb_sectors;
	Uint32	nb_mesh;
	Uint32	nb_entities;
	Uint32	nb_lights;
	Uint32	nb_polygons;
	Uint32	nb_walls;
	Uint32	nb_textures;
	Uint32	nb_pixels;
}				t_counter;

typedef struct	s_map_file_symbol
{
	char			name[12];
	t_symbol_type	type;
}				t_map_file_symbol;

typedef struct	s_map_file_function
{
	char				name[12];
	uint64_t			code_size;
	uint64_t			alias_size;
	uint64_t			needed_symbols;
	char				code[0];
	t_ptr_type			alias[0];
	t_map_file_symbol	symbol[0];
}				t_map_file_function;

t_map_file		*world_to_map_file(t_world *w);
t_world			map_file_to_world(t_map_file *stream);
t_counter		count_world(t_world *w);

#endif
