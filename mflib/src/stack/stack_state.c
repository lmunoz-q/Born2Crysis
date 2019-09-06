/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:54:36 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/16 11:56:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstack.h"

t_bool			stack_isempty(t_stack *stack)
{
	if (!stack)
		return (TRUE);
	if (stack->top == -1)
		return (TRUE);
	return (FALSE);
}

t_bool			stack_isfull(t_stack *stack)
{
	if (!stack)
		return (FALSE);
	if (stack->top == stack->maxdata - 1)
		return (TRUE);
	return (FALSE);
}
