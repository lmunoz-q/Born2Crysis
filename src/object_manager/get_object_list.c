/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 21:31:17 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/19 21:34:22 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_manager.h"

t_list2		*get_object_list()
{
	static t_list2	*object_list = NULL;

	if (object_list == NULL)
		object_list = list2_create();
	return (object_list);
}