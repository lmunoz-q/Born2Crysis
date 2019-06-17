/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:56:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/17 13:38:11 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "mflib.h"
# include <libui.h>
# include "world.h"
# include "texture_manager.h"
# include "thread_pool.h"
# include "camera.h"

typedef struct	s_raster
{
	double		start;
	double		end;
	double		zstart;
	double		zend;
	double		ustart;
	double		uend;
	double		vstart;
	double		vend;
	double		lstart;
	double		lend;
	double		x_s;
	double		x_s2;
	double		x_s3;
	double		z_s;
	double		z_s2;
	double		z_s3;
	double		u_s;
	double		u_s2;
	double		u_s3;
	double		v_s;
	double		v_s2;
	double		v_s3;
	double		l_s;
	double		l_s2;
	double		l_s3;
}				t_raster;

typedef struct	s_edge
{
	double		*p;
	double		*uv;
	double		*l;
	double		dist;
}				t_edge;

typedef struct	s_clipper
{
	t_stack		*inside;
	t_stack		*outside;
}				t_clipper;

/*
** PUBLIC
** RENDER FUNCS
*/
void			render_sector(t_sector *sector, t_camera *cam, SDL_Surface *surface);
void			render_mesh(t_mesh *mesh, t_camera *cam, SDL_Surface *surface);

/*
** PRIVATE
** INTERNAL RENDERING FUNCS
** NO TOUCHIE! NO!
*/
int				model_to_world(t_mesh *mesh, double pos[3], t_polygon *p);
void			world_to_view(t_polygon *p, int count, double view_mat[4][4]);
void			view_to_projection(t_polygon *p, int count, double proj_mat[4][4], SDL_Surface *surface);
void			rasterize(t_polygon *p, int count, SDL_Surface *surface);
void			init_raster(t_polygon *p, t_raster *e);


/*
** CLIPPER FUNCS
*/
int				portal_clip(t_polygon *p, int count, int width, int height);
int				clip_znear(t_polygon *p, int count);
void			clip_2out1in_z(t_clipper *c);
void			edge_to_polygon(t_edge *e, t_polygon *p, int i);
t_clipper		*init_clipper();
void			init_edge(t_polygon	*p, t_edge edge[3]);

/*
**	ZBUFF FUNCTIONS
*/
double			*init_zbuff(size_t size);
double			*get_zbuff();
void			reset_zbuff(double value, size_t size);

#endif
