/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clipper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:42:25 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/07 14:48:08 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_clipper		*init_clipper(void)
{
	static t_clipper clip = {.in = NULL, .out = NULL};

	if (!clip.in)
		clip.in = stack_create(3);
	if (!clip.out)
		clip.out = stack_create(3);
	if (clip.in && clip.out)
	{
		stack_reset(clip.out, FALSE);
		stack_reset(clip.in, FALSE);
		return (&clip);
	}
	return (NULL);
}
