/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 20:12:27 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/09 20:16:35 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int		clip_screen(t_polygon *p, int count, int width, int height)
{
	count = clip_against_plane(p, count, (double [3]){0, 0, 0}, (double [3]){1, 0, 0});
	count = clip_against_plane(p, count, (double [3]){0, 0, 0}, (double [3]){0, 1, 0});
	count = clip_against_plane(p, count, (double [3]){width, height, 0}, (double [3]){-1, 0, 0});
	count = clip_against_plane(p, count, (double [3]){width, height, 0}, (double [3]){0, -1, 0});
	return (count);
}