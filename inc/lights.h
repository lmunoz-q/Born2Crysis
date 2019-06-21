/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:57:44 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/18 10:01:27 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

enum	e_light_type
{
	POINT_LIGHT,
	DIRECTIONAL_LIGHT
};

typedef struct			s_light
{
	enum e_light_type	type;
	double				pos_o[4];
	double				pos[4];
	double				dir[3];
	double				intensity;
	double				mat[4][4];
}						t_light;

typedef struct			s_light_comp
{
	t_light				*lights;
	int					light_count;
}						t_light_comp;

#endif
