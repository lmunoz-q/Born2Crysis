/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 18:35:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/11 16:56:37 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

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

	t_libui_widget preview_container;
	t_libui_widget view_container;
} t_editor_interface;

typedef struct		s_editor
{
	
}					t_editor;


#endif
