/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_transparent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 13:13:48 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/09 14:04:04 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static t_bool		trans_sort_by_z(void *f, void *s)
{
	t_polygon *ff;
	t_polygon *ss;

	ff = f;
	ss = s;
	if (ff->v01.a[2] >= ss->v01.a[2])
		return (TRUE);
	return (FALSE);
}

void		draw_transparent(SDL_Surface *surf)
{
	t_trans_buffer	*tb;

	if (!(tb = get_transbuff()))
		return ;
	mf_quicksort_c(tb->data, (int [2]){0, tb->top}, trans_sort_by_z, sizeof(t_polygon));
	rasterize(tb->data, tb->top + 1, surf, TRUE);
	tb->top = -1;
}
