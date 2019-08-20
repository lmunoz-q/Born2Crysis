/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ints.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 14:48:35 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/18 17:50:05 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

void				get_ints_format_one(t_list2 *l, char *line)
{
	t_indice	*indice;
	int			i;

	if (!(indice = (t_indice *)malloc(sizeof(t_indice))))
		return ;
	i = -1;
	while (++i < 3)
	{
		while (mf_isspace(*line) == TRUE)
			line++;
		indice->v[i] = mf_atoi(line);
		while (mf_isdigit(*line) == TRUE)
			line++;
	}
	list2_push(l, indice);
}

void				get_ints_format_two(t_list2 *l, char *line)
{
	t_indice	*indice;
	int			i;

	if (!(indice = (t_indice *)malloc(sizeof(t_indice))))
		return ;
	i = -1;
	while (++i < 3)
	{
		while (mf_isspace(*line))
			line++;
		indice->v[i] = mf_atoi(line);
		while (mf_isdigit(*line))
			line++;
		line++;
		indice->uv[i] = mf_atoi(line);
		while (mf_isdigit(*line))
			line++;
	}
	list2_push(l, indice);
}

void				get_ints_format_three(t_list2 *l, char *line)
{
	t_indice	*indice;
	int			i;

	if (!(indice = (t_indice *)malloc(sizeof(t_indice))))
		return ;
	i = -1;
	while (++i < 3)
	{
		while (mf_isspace(*line))
			line++;
		indice->v[i] = mf_atoi(line);
		while (mf_isdigit(*line))
			line++;
		line++;
		indice->uv[i] = mf_atoi(line);
		while (mf_isdigit(*line))
			line++;
		line++;
		indice->n[i] = mf_atoi(line);
		while (mf_isdigit(*line))
			line++;
	}
	list2_push(l, indice);
}
