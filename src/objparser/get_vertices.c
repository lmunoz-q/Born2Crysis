/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vertices.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:17:46 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/28 19:17:47 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

void				get_vertices(t_list2 *l, char *line, int num)
{
	double	*vertices;
	int		i;

	if (!(vertices = (double *)SDL_calloc(sizeof(double), num)))
		return ;
	i = -1;
	while (++i < num)
	{
		while (mf_isspace(*line))
			line++;
		vertices[i] = mf_atof(line);
		while (mf_isdigit(*line) || *line == '.' || *line == '-')
			line++;
	}
	list2_pushback(l, vertices);
}
