/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:37:37 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/18 14:34:47 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstack.h"

void			*stack_pop(t_stack *stack)
{
	void	*tmp;

	if (!stack)
		return (NULL);
	if (stack->top != -1)
	{
		tmp = stack->data[stack->top];
		stack->data[stack->top] = NULL;
		stack->top--;
		return (tmp);
	}
	return (NULL);
}
