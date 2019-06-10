/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 20:44:45 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/10 01:28:39 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_MANAGER_H
# define TEXTURE_MANAGER_H

# include "libui.h"
# include "mflib.h"

typedef enum		e_texture_mode
{
					TX_REPEAT,
					TX_CLAMP_EDGES
}					t_texture_mode;

typedef struct		s_texture
{
	unsigned int	id;
	SDL_Surface		*texture;
	t_vec2i			size;
	t_texture_mode	mode;
}					t_texture;

t_list2				*get_texture_list();
t_list2				*load_texture(char *path);

#endif