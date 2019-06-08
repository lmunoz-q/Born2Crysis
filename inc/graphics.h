/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:56:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/08 13:01:03 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "mflib.h"
# include <libui.h>
# include "world.h"
# include "camera.h"

typedef struct	s_raster
{
	double		dx;
	double		dy;
	double		dz;
	double		du;
	double		dv;
	double		dl;
	double		dx2;
	double		dy2;
	double		dz2;
	double		du2;
	double		dv2;
	double		dl2;
	double		dx3;
	double		dy3;
	double		dz3;
	double		du3;
	double		dv3;
	double		dl3;
	double		dx_step;
	double		dx_step2;
	double		dz_step;
	double		dz_step2;
	double		du_step;
	double		du_step2;
	double		dl_step;
	double		dl_step2;
	double		dx_step3;
	double		dz_step3;
	double		du_step3;
	double		dl_step3;
	double		dv_step;
	double		dv_step2;
	double		dv_step3;
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
	double		zstep;
	double		lstep;
	double		ustep;
	double		vstep;
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

/*
** PRIVATE
** INTERNAL RENDERING FUNCS
** NO TOUCHIE! NO!
*/
int				model_to_world(t_mesh *mesh, double pos[3], t_polygon *p);
void			world_to_view(t_polygon *p, int count, double view_mat[4][4]);


/*
** CLIPPER FUNCS
*/
int				clip_against_plane(t_polygon *p, int count, double plane_p[3], double plane_n[3]);
t_clipper		*init_clipper();
void			init_edge(t_polygon	*p, t_edge edge[3]);
double			calc_ratio_3d(t_edge *e1, t_edge *e2);
void			clip_2out1in(t_clipper *c);
/*
void		world_to_view(t_polygonlist *v, double view_matrix[4][4]);
void		clip_polygons_2d(t_polygonlist	*l, t_vec2i win_size);
void		clip_znear(t_polygonlist *l);
void		purge_clipped_polygons(t_polygonlist *l);
void		view_to_projection(t_polygonlist *l, double mat[4][4], t_vec2i size);
void		rasterize(t_polygonlist *l, t_libui_window *win);

void		render_object(t_camera *cam, t_libui_window *win, t_object *object);
void		render_sector(	t_world *world, int sector_id,
							SDL_Surface *s, t_camera *cam);

/*
**	GRAPHICS UTILS

void		init_edge(t_polygon	*p, t_edge *edge);
*/

#endif
