/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:05:37 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/22 19:23:14 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEM_H
# define ITEM_H

typedef struct		s_item_stats
{
	int				attack_dmg;
	int				armor;
	int				durability;
	int				weight;
	int				size;
}					t_item_stats;

typedef struct		s_item
{
	int				id;
	char			name[32];
	t_item_stats	stats;
	void			*(*f)(void *);
	void			*param;
	void			*model;
}					t_item;

t_item				*item_create(int id, char *name);
void				item_set_main_act(t_item *i, void *(*f)(void *), void *p);

/*
**		TODO: CREATE FUNCTIONS TO SET AND CREATE NEW ITEMS
**		TODO: DELETE ITEM FUNCTION
*/

#endif
