/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 13:33:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 15:56:37 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJPARSER_H
# define OBJPARSER_H

# include "world.h"
# include "mflib.h"
# include "texture_manager.h"

typedef struct		s_indices
{
	int				v[3];
	int				uv[3];
	int				n[3];
}					t_indice;

typedef struct		s_obj
{
	t_list2			*vertices;
	t_list2			*vertices_uv;
	t_list2			*normals;
	void			**vertices_s;
	void			**vertices_uv_s;
	void			**normals_s;
	int				size_v;
	int				size_uv;
	int				size_n;
	t_list2			*indices;
	t_bool			has_normals;
	t_bool			has_texture;
}					t_obj;

t_obj				*load_obj(char *path);
void				destroy_obj(t_obj **obj);
t_mesh				*obj_to_mesh(t_obj *obj, char *img, t_texture_mode mode);

/*
**	UTILS
*/
void				get_ints_format_one(t_list2 *l, char *line);
void				get_ints_format_two(t_list2 *l, char *line);
void				get_ints_format_three(t_list2 *l, char *line);
void				read_line(t_obj *obj, char *line);

#endif
