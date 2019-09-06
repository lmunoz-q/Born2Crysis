/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:31:51 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/21 21:52:44 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_manager.h"

void		destroy_texture(t_texture **texture)
{
	SDL_FreeSurface((*texture)->texture);
	free(*texture);
	*texture = NULL;
}
