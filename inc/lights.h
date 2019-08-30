/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:57:44 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/30 13:08:52 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include <mflib.h>
# include <SDL2/SDL.h>

enum	e_light_type
{
	POINT_LIGHT,
	DIRECTIONAL_LIGHT
};

typedef struct			s_light
{
	int32_t				type;
	int32_t				id;
	t_vec4d				pos_o;
	t_vec4d				pos;
	t_vec3d				dir;
	double				intensity;
	t_mat4d				mat;
	double				fallof;
}						t_light;

typedef struct			s_light_comp
{
	t_light				*lights;
	int32_t				light_count;
}						t_light_comp;

void		light_add(t_light_comp *comp, t_light light);
int			light_delete(t_light_comp *lcomp, int index);

#endif
