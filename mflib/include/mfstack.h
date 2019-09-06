/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mfstack.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:06:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/06 20:24:29 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MFSTACK_H
# define MFSTACK_H

# include "boolean.h"
# include "stdlib.h"

typedef struct	s_stack
{
	int			top;
	void		**data;
	int			maxdata;
}				t_stack;

t_bool			stack_isempty(t_stack *stack);
t_bool			stack_isfull(t_stack *stack);
t_stack			*stack_create(size_t size);
void			stack_destroy(t_stack **stack);
void			*stack_top(t_stack *stack);
void			stack_push(t_stack *stack, void *data);
void			*stack_pop(t_stack *stack);
/*
** stack_next_to_top returns the item right under the top item.
**
** RETURNS: second last item, or NULL if stack is invalid or not enough items.
*/
void			*stack_next_to_top(t_stack *stack);
void			stack_reset(t_stack *stack, t_bool f);

#endif
