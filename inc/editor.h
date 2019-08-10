/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 18:35:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/10 13:40:08 by mfischer         ###   ########.fr       */
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

	t_libui_widget select_container;
	t_libui_widget select_label;
	t_libui_widget selected_file_label;
} t_editor_interface;

typedef struct		s_editor
{
	SDL_Surface		*world_surface;
	SDL_Surface		*ocject_preview_surface;
}					t_editor;


#endif
