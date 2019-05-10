/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:56:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/10 22:32:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "mflib.h"
# include <libui.h>
# include "world.h"
# include "camera.h"

typedef struct	s_edge
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
	double		start;
	double		end;
	double		zstart;
	double		zend;
	double		uvstart;
	double		uvend;
	double		lstart;
	double		lend;
	double		zstep;
	double		lstep;
	double		uvstep;
}				t_edge;

void		model_to_world(t_polygonlist *v, double matrix[4][4]);
void		world_to_view(t_polygonlist *v, double view_matrix[4][4]);
void		cull_backfaces(t_polygonlist *v, double mouse_dir[3]);
void		purge_clipped_polygons(t_polygonlist *l);
void		view_to_projection(t_polygonlist *l, double mat[4][4], t_vec2i size);
void		rasterize(t_polygonlist *l, t_libui_window *win);

#endif
