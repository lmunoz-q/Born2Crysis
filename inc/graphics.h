/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:56:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/09 20:59:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "mflib.h"
# include <libui.h>
# include "world.h"

typedef struct	s_edge
{
	double		dx;
	double		dy;
	double		dz;
	double		du;
	double		dw;
	double		dl;
	double		dx2;
	double		dy2;
	double		dz2;
	double		du2;
	double		dw2;
	double		dl2;
}				t_edge;


void		model_to_world(t_polygonlist *v, double matrix[4][4]);
void		world_to_view(t_polygonlist *v, double view_matrix[4][4]);
void		cull_backfaces(t_polygonlist *v, double mouse_dir[3]);
void		purge_clipped_polygons(t_polygonlist *l);

#endif
