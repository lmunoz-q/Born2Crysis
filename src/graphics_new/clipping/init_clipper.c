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

t_clipper		*init_clipper()
{
	static t_clipper clip = {.inside = NULL, .outside = NULL};

	if (!clip.inside)
		clip.inside = stack_create(3);
	if (!clip.outside)
		clip.outside = stack_create(3);
	if (clip.inside && clip.outside)
	{
		stack_reset(clip.outside, FALSE);
		stack_reset(clip.inside, FALSE);
		return (&clip);
	}
	return (NULL);
}