/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer_ref.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 19:57:18 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/10 13:45:41 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void init_raster(t_vertex *vertex, t_edge *e)
{
    if (vertex->v12_conv[1] < vertex->v01_conv[1])
        mf_swap_doubles(vertex->v12_conv, vertex->v01_conv, 3);
    if (vertex->v20_conv[1] < vertex->v01_conv[1])
        mf_swap_doubles(vertex->v20_conv, vertex->v01_conv, 3);
    if (vertex->v20_conv[1] < vertex->v12_conv[1])
        mf_swap_doubles(vertex->v20_conv, vertex->v12_conv, 3);
    e->dx = vertex->v12_conv[0] - vertex->v01_conv[0];
    e->dy = vertex->v12_conv[1] - vertex->v01_conv[1];
    e->dx2 = vertex->v20_conv[0] - vertex->v01_conv[0];
    e->dy2 = vertex->v20_conv[1] - vertex->v01_conv[1];
    e->dz = vertex->v12_conv[2] - vertex->v01_conv[2];
    e->dz2 = vertex->v20_conv[2] - vertex->v01_conv[2];
    e->dx_step = (e->dy) ? e->dx / fabs(e->dy) : 0.0;
    e->dx_step2 = (e->dy2) ? e->dx2 / fabs(e->dy2) : 0.0;
    e->dz_step = (e->dy) ? e->dz / fabs(e->dy) : 0.0;
    e->dz_step2 = (e->dy2) ? e->dz2 / fabs(e->dy2) : 0.0;
}

void        rasterize_fill(t_polygonlist *polygon, t_libui_window *win, double  **zbuff)
{
    t_edge  e;
    int     i;
    int     j;
    double  start;
    double  end;
    double  zstart, zend;
    double  ztmp;
    double  t_step;

    i = -1;
    while (++i < polygon->vertexnum)
    {

        if (!polygon->vertices[i].active)
            continue ;
        init_raster(&polygon->vertices[i], &e);
        j = polygon->vertices[i].v01_conv[1];
        while ((e.dy) && ++j < polygon->vertices[i].v12_conv[1])
        {
            start = polygon->vertices[i].v01_conv[0] + ((double)j - polygon->vertices[i].v01_conv[1]) * e.dx_step;
            end = polygon->vertices[i].v01_conv[0] + ((double)j - polygon->vertices[i].v01_conv[1]) * e.dx_step2;
            zstart = polygon->vertices[i].v01_conv[2] + ((double)j - polygon->vertices[i].v01_conv[1]) * e.dz_step;
            zend = polygon->vertices[i].v01_conv[2] + ((double)j - polygon->vertices[i].v01_conv[1]) * e.dz_step2;
            if (start > end)
            {
                mf_swap_doubles(&zstart, &zend, 1);
                mf_swap_doubles(&start, &end, 1);
            }
            t_step = (zend - zstart) / (end - start);
            ztmp = zstart;
            while (start < end)
            {
                if (start >= 0 && end < win->surface->w && j >= 0 && j < win->surface->h && zbuff[j][(int)start] > ztmp)
                {
                    zbuff[j][(int)start] = ztmp;
                    ((int *)win->surface->pixels)[(int)((j * win->surface->w) + start)] = polygon->vertices[i].newcolor;
                }
                ztmp += t_step;
                start++;

            }
        }
        e.dx = polygon->vertices[i].v20_conv[0] - polygon->vertices[i].v12_conv[0];
        e.dy = polygon->vertices[i].v20_conv[1] - polygon->vertices[i].v12_conv[1];
        e.dz = polygon->vertices[i].v20_conv[2] - polygon->vertices[i].v12_conv[2];
        e.dx_step = (e.dy) ? e.dx / fabs(e.dy) : e.dx_step;
        e.dz_step = (e.dy) ? e.dz / fabs(e.dy) : e.dz_step;
        while ((e.dy) && j < polygon->vertices[i].v20_conv[1])
        {
            start = polygon->vertices[i].v12_conv[0] + (j - polygon->vertices[i].v12_conv[1]) * e.dx_step;
            end = polygon->vertices[i].v01_conv[0] + ((double)j - polygon->vertices[i].v01_conv[1]) * e.dx_step2;
            zstart = polygon->vertices[i].v12_conv[2] + (j - polygon->vertices[i].v12_conv[1]) * e.dz_step;
            zend = polygon->vertices[i].v01_conv[2] + ((double)j - polygon->vertices[i].v01_conv[1]) * e.dz_step2;
            if (start > end)
            {
                mf_swap_doubles(&start, &end, 1);
                mf_swap_doubles(&zstart, &zend, 1);
            }
            t_step = (zend - zstart) / (end - start);
            ztmp = zstart;
            while (start < end)
            {
                if (start >= 0 && end < win->surface->w && j >= 0 && j < win->surface->h && zbuff[j][(int)start] > ztmp)
                {
                    zbuff[j][(int)start] = ztmp;
                    ((int *)win->surface->pixels)[(int)((j * win->surface->w) + start)] = polygon->vertices[i].newcolor;
                }
                ztmp += t_step;
                start++;
            }
            j++;
        }
    }
}
