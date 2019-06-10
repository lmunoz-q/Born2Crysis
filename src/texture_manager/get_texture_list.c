/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 21:12:39 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/09 21:16:10 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

t_list2				*get_texture_list()
{
	static t_list2	*tex_list = NULL;

	if (!tex_list)
		tex_list = list2_create();
	return (tex_list);
}