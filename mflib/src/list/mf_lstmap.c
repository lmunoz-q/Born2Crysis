/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:48:10 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/15 17:46:51 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist.h"

t_list	*mf_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *head;
	t_list *tail;

	if (!lst || !f)
		return (NULL);
	tail = mf_lstnew((*f)(lst)->content, (*f)(lst)->content_size);
	head = tail;
	while (lst->next)
	{
		lst = lst->next;
		tail->next = mf_lstnew((*f)(lst)->content, (*f)(lst)->content_size);
		tail = tail->next;
	}
	tail->next = NULL;
	return (head);
}
