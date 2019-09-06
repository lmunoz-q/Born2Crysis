/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mf_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:00:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/15 17:50:45 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mflist.h"
#include "mfmemory.h"

t_list	*mf_lstnew(void const *content, size_t content_size)
{
	t_list	*ls;

	if (!(ls = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		if (!(ls->content = mf_memalloc(content_size)))
			return (NULL);
		ls->content = mf_memcpy(ls->content, (void *)content, content_size);
		ls->content_size = content_size;
	}
	else
	{
		ls->content = NULL;
		ls->content_size = 0;
	}
	ls->next = NULL;
	return (ls);
}
