/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:30:12 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/16 11:34:37 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstack.h"

void	stack_push(t_stack *stack, void *data)
{
	if (!data)
		return ;
	if (stack->top < stack->maxdata - 1)
	{
		stack->top++;
		stack->data[stack->top] = data;
	}
}
