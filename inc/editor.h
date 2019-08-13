/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 18:35:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/13 21:03:06 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "graphics.h"

#define EDITOR_MENU_WIDTH 500

typedef struct s_editor_interface
{
	TTF_Font		*font;

	t_libui_widget  editor_container;
	t_libui_widget	save_textbutton;
	t_libui_widget	new_textbutton;
	t_libui_widget	wall_textbutton;
	t_libui_widget	obj_textbutton;

	t_libui_widget	select_container;
	t_libui_widget	select_label;
	t_libui_widget	selected_file_label;

	t_libui_widget	preview_container;
	t_libui_widget	view_container;

	t_camera		editor_cam;
} t_editor_interface;


/*
** PREVIEW FUNCS
*/
void		render_object_preview(t_object *obj, SDL_Surface *surf, t_vec2i size);
void 		render_editor_view(t_world *world, t_editor_interface *ei);

#endif
