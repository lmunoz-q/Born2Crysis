/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_next_to_top.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:19:50 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/06 20:20:50 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstack.h"

void	*stack_next_to_top(t_stack *stack)
{
	if (!stack)
		return (NULL);
	if (stack->top > 0)
		return (stack->data[stack->top - 1]);
	return (NULL);
}
