/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:50:27 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/29 16:53:11 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfstack.h"

void		stack_reset(t_stack *stack, t_bool f)
{
	int		i;
	void	*data;

	i = -1;
	while (++i < stack->maxdata)
	{
		data = stack_pop(stack);
		if (f)
			free(data);
	}
}
