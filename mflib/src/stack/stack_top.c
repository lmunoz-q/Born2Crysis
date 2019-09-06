/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_top.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:34:59 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/17 18:51:25 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstack.h"

void			*stack_top(t_stack *stack)
{
	if (!stack)
		return (NULL);
	if (stack->top != -1)
		return (stack->data[stack->top]);
	return (NULL);
}
