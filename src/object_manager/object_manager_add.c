/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_manager_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 22:00:45 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 17:02:59 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_manager.h"

int			object_manager_add(char *path)
{
	t_list2				*list;
	t_object_resource	*obj_res;

	if (!(list = get_object_list()))
		return (-1);
	if (!(obj_res = (t_object_resource *)malloc(sizeof(t_object_resource))))
		return (-1);
	mf_strcpy(obj_res->object_name, path);
	obj_res->object = load_obj(path);
	list2_push(list, obj_res);
	return (1);
}
