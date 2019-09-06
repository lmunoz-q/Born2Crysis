/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:09:43 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/19 21:32:12 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist2.h"

t_list2				*list2_create(void)
{
	t_list2		*list;

	if (!(list = (t_list2 *)malloc(sizeof(t_list2))))
		return (NULL);
	list->size = 0;
	list->list = NULL;
	return (list);
}
