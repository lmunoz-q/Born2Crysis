/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 20:44:45 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/10 19:07:42 by mfischer         ###   ########.fr       */
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
}					t_texture_s, *t_texture;

t_list2				*get_texture_list();
t_texture			init_texture(const char *path, t_texture_mode mode);
void				destroy_texture(t_texture *texture);
void				load_texture_from_bmp(char *path, t_texture_mode mode);
t_texture			get_texture_from_id(int id);
t_texture			get_current_texture(void);
void				load_texture(int id);
int					texture_get_pixel(int y, int x);

#endif