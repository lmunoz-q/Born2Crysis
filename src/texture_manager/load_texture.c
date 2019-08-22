/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:14:09 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/21 21:53:41 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

static t_texture	*set_texture(t_texture *tex)
{
	static t_texture	*texture = NULL;

	if (tex != NULL)
		texture = tex;
	return (texture);
}

t_texture			*get_current_texture(void)
{
	return (set_texture(NULL));
}

void				load_texture(unsigned int id)
{
	t_texture *tmp;

	tmp = set_texture(NULL);
	if (tmp && tmp->id == id)
		return ;
	set_texture(get_texture_from_id(id));
}
