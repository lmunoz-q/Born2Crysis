/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:56:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/27 16:44:55 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# define TRANS_BUFF_SIZE 10000

# include "mflib.h"
# include <libui.h>
# include "world.h"
# include "texture_manager.h"
# include "objparser.h"
# include "thread_pool.h"
# include "camera.h"

# define R 0x00ff0000
# define G 0x0000ff00
# define B 0x000000ff
# define A 0xff000000

typedef struct		s_raster
{
	int				start;
	int				end;
	double			zstart;
	double			zend;
	double			ustart;
	double			uend;
	double			vstart;
	double			vend;
	double			lstart;
	double			lend;
	double			wstart;
	double			wend;
	double			x_s;
	double			x_s2;
	double			x_s3;
	double			z_s;
	double			z_s2;
	double			z_s3;
	double			u_s;
	double			u_s2;
	double			u_s3;
	double			v_s;
	double			v_s2;
	double			v_s3;
	double			l_s;
	double			l_s2;
	double			l_s3;
	int				transparency;
	int				h;
	int				w;
	t_texture		*tex;
	double			*zbuff;
	uint32_t		*pix;
}					t_raster;

typedef struct		s_edge
{
	int				newcount;
	t_vec4d			*p;
	t_vec2d			*uv;
	double			*l;
	double			dist;
}					t_edge;

typedef struct		s_clipper
{
	t_stack			*in;
	t_stack			*out;
}					t_clipper;

typedef struct		s_trans_buffer
{
	int				top;
	int				size;
	t_polygon		*data;
}					t_trans_buffer;

typedef struct		s_2v3d2i
{
	t_vec3d			tmp;
	t_vec3d			tmp_n;
	int				j;
	int				i;
}					t_2v3d2i;

/*
** PUBLIC
** RENDER FUNCS
*/
void			render_sector(t_sector *sector, t_camera *cam, SDL_Surface *surface, t_mesh *portal);
void			render_mesh(t_mesh *mesh, t_camera *cam, SDL_Surface *surface, t_light_comp *lcomp);
void			render_invisible_mesh(t_mesh *mesh, t_camera *cam, SDL_Surface *surface, t_light_comp *lcomp);
void			openworld_render(t_world *world, t_camera *cam, SDL_Surface *surf, int sector_id);

/*
** PRIVATE
** INTERNAL RENDERING FUNCS
** NO TOUCHIE! NO!
*/
Uint32				model_to_world(t_mesh *mesh, t_vec4d pos, t_polygon *p);
void				world_to_view(t_polygon *p, int count, t_mat4d view_mat);
void				view_to_projection(t_polygon *p, int count,
					t_mat4d proj_mat, SDL_Surface *surface);
void				rasterize(t_polygon *p, int count, SDL_Surface *surface,
					t_bool trans);
void				init_raster(t_polygon *p, t_raster *e);
void				sort_vertices(t_polygon *p);
void				polygons_set_trans(t_polygon *p, int size, int transparency);
void			draw_alpha_line(t_raster *e, double *zbuff, Uint32 *p,
	t_vec4d steps);

/*
** CLIPPER FUNCS
*/
Uint32				portal_clip(t_polygon *p, Uint32 count, int width,
	int height);
Uint32				clip_znear(t_polygon *p, Uint32 count);
void				clip_2out1in_z(t_clipper *c);
void				edge_to_polygon(t_edge *e, t_polygon *p, int i);
t_clipper			*init_clipper();
void				init_edge(t_polygon	*p, t_edge edge[3]);

/*
**	ZBUFF FUNCTIONS
*/
double				*init_zbuff(size_t size);
double				*get_zbuff();
void				reset_zbuff(double value, size_t size);

/*
** LIGHT FUNCTIONS
*/
void				light_to_world(t_light_comp *comp);
void				calculate_lighting(t_polygon *p, int count,
					t_light_comp *lcomp);

/*
**	SECTOR QUEUE FUNCTIONS
*/
t_sector			*sector_queue_push(t_sector *sector);
t_sector			*sector_queue_pop();

/*
**	PORTALS
*/
void				portal_cull(t_mesh *m, int mn, t_mesh *portal,
					t_vec4d cam_pos);

/*
**	TRANSPARENCY FUNCTIONS
*/
t_trans_buffer		*get_transbuff(void);
void				transbuff_push(t_polygon *p);
t_polygon			*transbuff_pop();
void				draw_transparent(SDL_Surface *surf);

/*
**	SKYBOX FUNCTIONS
*/
void				skybox_load(t_world *world, char *path);
void				skybox_set_pos(t_mesh *skybox, t_vec3d pos);

/*
**	GRAPHICS THREADS
*/
typedef enum		e_gthread_type
{
	GTHREAD_GAME,
	GTHREAD_PREVIEW,
	GTHREAD_EDITOR,
	GTHREAD_LAST
}					t_gthread_type;

typedef struct		s_gworker
{
	int				id;
	pthread_t		thread;
	uint32_t		*pixels;
	double			*zbuff;
	int				start;
	int				end;
	void			*parent;
	t_bool			pending;
}					t_gworker;

typedef struct		s_gthreads
{
	t_bool			alive;
	t_gworker		*workers;
	int				worker_count;
	int				active;
	pthread_cond_t	work_cnd;
	pthread_mutex_t	work_mtx;
	t_bool			work;
	pthread_cond_t	wait_cnd;
	pthread_mutex_t	wait_mtx;
	t_bool			wait;
	double			delta;
	int				h;
	int				w;
	t_bool			trans;
	t_polygon		*plist;
	Uint32			polygon_count;
	int				work_load;
}					t_gthreads;

t_gthreads			*gthread_init(short	workers, SDL_Surface *s, t_polygon *p,
	t_gthread_type type);
t_gthreads			*gthread_get(t_gthread_type type);
void				gthread_wait(t_gthreads *gt);
void				*gthread_work(void *p);
void				gthread_raster(t_gthreads *gt, t_gworker *w);
void				gthread_launch(t_gthreads *gt);
void				gthread_destroy(t_gthreads *gt);
void				clip_2o1i(t_stack *out, t_stack *in, t_vec2d edge[2]);
void				clip_1o2i(t_clipper *c, t_vec2d edge[2], t_polygon *p,
	t_polygon *o);
t_vec2d				line_intsect_2d(t_vec2d a1, t_vec2d a2, t_vec2d b1,
	t_vec2d b2);
double				get_intsec_r(t_vec2d a1, t_vec2d a2, t_vec2d b1,
	t_vec2d b2);

#endif
