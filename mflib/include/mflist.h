/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mflist.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:22:43 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/30 12:58:09 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MFLIST_H
# define MFLIST_H

# include <stdlib.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*mf_lstnew(void const *content, size_t content_size);
void				mf_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				mf_lstdel(t_list **alst, void (*del)(void *, size_t));
void				mf_lstadd(t_list **alst, t_list *new);
void				mf_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*mf_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t				mf_lstcount(t_list *lst);

#endif
