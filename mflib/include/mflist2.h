/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mflist2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 13:17:10 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/30 12:57:53 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MFLIST2_H
# define MFLIST2_H

# include <stdlib.h>

typedef struct		s_node
{
	void			*data;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct		s_list2
{
	t_node			*list;
	int				size;
}					t_list2;

t_list2				*list2_create();

/*
** Adds element to front.
** Returns 1 on success, otherwise 0.
*/
int					list2_push(t_list2 *list, void *data);

/*
** Adds element to back.
** Use push if performance is critical.
** Returns 1 on success, otherwise 0.
*/
int					list2_pushback(t_list2 *list, void *data);
void				list2_insert(t_list2 *list, t_node *node, void *data);
void				*list2_delete(t_list2 *list, t_node *node);
void				*list2_pop(t_list2 *list);
void				*list2_popback(t_list2	*list);
void				*list2_at(t_list2 *list, int index);
void				list2_destroy(t_list2 **list);
void				**list2_toarray(t_list2 *list, int *list_size);

#endif
