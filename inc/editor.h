/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 18:35:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/18 13:47:39 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "graphics.h"

#define EDITOR_MENU_WIDTH 500

#define FLY_SPEED			0.3
#define MAX_SECTEURS 500 // defini le numero maximum du secteur selectionnable
#define SECTEUR_TEXT "Secteur courant: "
#define SECTEUR_TEXT_SIZE 20


typedef struct s_editor_interface
{
	TTF_Font		*font;

	t_libui_widget  editor_container;
	t_libui_widget	save_textbutton;
	t_libui_widget	new_textbutton;
	t_libui_widget	wall_textbutton;
	t_libui_widget	obj_textbutton;

	t_libui_widget secteur_selec_label;
	t_libui_widget secteur_selec_up_button;
	t_libui_widget secteur_selec_down_button;
	unsigned int	secteur_courant;

	t_libui_widget	select_container;
	t_libui_widget	select_label;
	t_libui_widget	selected_file_label;

	t_libui_widget	preview_container;
	t_libui_widget	view_container;

	t_mat4d			preview_mat;
	t_mat4d			item_mat;
	t_mat4d			item_scale_mat;
	t_mat4d			item_rotation_mat;

	t_camera		editor_cam;

	void			*item_placer;
	t_bool			is_object;
} t_editor_interface;

# include "doom-nukem.h"

/*
** PREVIEW FUNCS
*/
void		render_preview(t_mesh *mesh, SDL_Surface *surf, t_vec2i size);
void 		render_editor_view(t_world *world, t_editor_interface *ei);

/*
** Gestion secteur courant
*/
void update_secteur_courant_text( t_libui_widget *label,
							unsigned int	new_value);
int increase_secteur_number(SDL_Event *		event,
							t_libui_widget *widget,
							void *			data);
int	decrease_secteur_number(SDL_Event *event, t_libui_widget *widget,
							void *data);

/*
** View functions
*/
void remplir_3dview(t_editor_interface *editor_interface, t_e *e);
void remplir_preview(t_editor_interface *editor_interface, t_e *e);

/*
** Editor boucle
*/
int toggle_capture_mouse(SDL_Event *event, t_libui_widget *widget, void *data);
int editor_event(t_e *e, t_libui_widgets_surface *ws,
								 t_editor_interface *editor_interface);
int editor_update(t_e *e, t_libui_widgets_surface *ws,
				  				t_editor_interface *editor_interface);
void editor_render(t_e *e, t_libui_widgets_surface *ws,
				   t_editor_interface *editor_interface);






#endif
