/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mtl_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:20:13 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/28 19:20:15 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

char	*get_mtl_name(char *line)
{
	while (*line && mf_isspace(*line))
		line++;
	while (*line && !mf_isspace(*line))
		line++;
	while (*line && mf_isspace(*line))
		line++;
	return (line);
}
