/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:57:44 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/27 13:33:30 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

#include <mflib.h>

enum	e_light_type
{
	POINT_LIGHT,
	DIRECTIONAL_LIGHT
};

typedef struct			s_light
{
	enum e_light_type	type;
	t_vec4d				pos_o;
	t_vec4d				pos;
	t_vec3d				dir;
	double				intensity;
// <<<<<<< HEAD
	t_mat4d				mat;
// =======
	double				fallof;
	// double				mat[4][4];
// >>>>>>> dev
}						t_light;

typedef struct			s_light_comp
{
	t_light				*lights;
	int					light_count;
}						t_light_comp;

#endif
