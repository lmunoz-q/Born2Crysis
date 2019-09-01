/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 14:50:23 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/31 23:47:45 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

static void	skybox_destroy(t_world *w)
{
	if (!w->skybox)
		return ;
	if (w->skybox->polygons)
		free(w->skybox->polygons);
	if (w->skybox->walls)
		free(w->skybox->walls);
	free(w->skybox);
	w->skybox = NULL;
}

static void	textures_destroy(t_world *w)
{
	int i;

	i = -1;
	while (++i < w->nb_textures)
		if (w->textures[i].texture)
			SDL_FreeSurface(w->textures[i].texture);
	w->nb_textures = 0;
	if (w->textures)
		free(w->textures);
}

static void	mesh_content_destroy(t_mesh *mesh)
{
	if (!mesh)
		return ;
	if (mesh->polygons)
		free(mesh->polygons);
	if (mesh->walls)
		free(mesh->walls);
}

void		world_destroy(t_world *w)
{
	int i;
	int j;

	i = -1;
	while (++i < w->sectornum)
	{
		if (w->sectors[i].entites)
			free(w->sectors[i].entites);
		if (w->sectors[i].lights.lights)
			free(w->sectors[i].lights.lights);
		j = -1;
		while (++j < w->sectors[i].meshnum)
			mesh_content_destroy(&w->sectors[i].mesh[j]);
		if (w->sectors[i].mesh)
			free(w->sectors[i].mesh);
	}
	skybox_destroy(w);
	textures_destroy(w);
}
