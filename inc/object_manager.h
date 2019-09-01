/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 20:59:44 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 13:00:23 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_MANAGER_H
# define OBJECT_MANAGER_H

# include "world.h"
# include "mflib.h"
# include "texture_manager.h"
# include "objparser.h"

typedef struct		s_object_resource
{
	t_obj			*object;
	char			object_name[1024];
}					t_object_resource;

t_list2				*get_object_list(void);
int					object_manager_add(char *path);
t_obj				*object_manager_get_obj(char *path);

#endif
