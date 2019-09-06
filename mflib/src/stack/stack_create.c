/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:18:40 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/16 11:33:51 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstack.h"

t_stack			*stack_create(size_t size)
{
	t_stack *stack;

	if (!(stack = (t_stack *)malloc(sizeof(t_stack))))
		return (NULL);
	stack->maxdata = size;
	stack->top = -1;
	if (!(stack->data = (void **)malloc(sizeof(void *) * size)))
	{
		free(stack);
		return (NULL);
	}
	return (stack);
}
