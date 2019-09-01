/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mtl_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 19:13:34 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/30 16:17:20 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objparser.h"

int					get_mtl_tex(char *line, char *path)
{
	int		fd;
	char	*nl;
	t_bool	right;
	int		tmp;

	tmp = -1;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (-1);
	right = FALSE;
	while (get_next_line(fd, &nl))
	{
		if (mf_strstr(nl, get_mtl_name(line)) && tmp == -1)
			right = TRUE;
		if (mf_strstr(nl, "map_Kd") && right)
		{
			right = FALSE;
			tmp = load_texture_from_x(get_mtl_name(nl), TX_REPEAT);
		}
		free(nl);
		nl = NULL;
	}
	if (nl)
		free(nl);
	close(fd);
	return (tmp);
}
