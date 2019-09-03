/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_delete_physics.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 11:31:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/03 12:29:52 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	mesh_delete_physics(t_mesh *m)
{
	if (m->nb_walls && m->walls)
	{
		m->nb_walls = 0;
		free(m->walls);
		m->walls = NULL;
	}
}