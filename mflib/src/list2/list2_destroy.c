/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 21:10:45 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/26 17:12:29 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist2.h"

static	void		recursive_free(t_node *head)
{
	if (head->next)
		recursive_free(head->next);
	free(head);
}

void				list2_destroy(t_list2 **list)
{
	if ((*list)->size > 0)
		recursive_free((*list)->list);
	free(*list);
	*list = NULL;
}
