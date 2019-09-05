/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 18:35:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/05 15:24:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "graphics.h"
# include "utilities.h"
# include "lights.h"
# include "libui.h"

# define EDITOR_MENU_WIDTH 500

# define FLY_SPEED 0.3
# define ROTATE_SPEED 1.0/180.0
# define MOD_ROT_SPEED 20.0/180.0
# define MAX_SECTEURS 500
# define SECTEUR_TEXT "Secteur courant: "
# define SECTEUR2_TEXT "Secteur secondaire: "
# define LUX_TYPE_TEXT "Lumiere type: "
# define LUX_TYPE_POINT_TEXT "point"
# define LUX_TYPE_DIRECTION_TEXT "direction"
# define SECTEUR_TEXT_SIZE 25

# define FRICTION_TYPE_TEXT "Friction mode: "
# define WALL_FRICTION_AUTO_TEXT "auto"
# define WALL_FRICTION_MAN_TEXT "manuel"
# define BASE_TEXT_SIZE 25

# define MAX_LUX_INTENSITY 25000.0
# define MAX_FALLOF_INTENSITY 25000.0
# define LUX_INTEN_TEXT "Intensite: "
# define LUX_FALLOF_TEXT "FallOf: "
# define LUX_TEXT_SIZE 25
# define WIREFRAME_COLOR 0xffff0000

# define SCRIPT_1_AIM "Script Enter"
# define SCRIPT_2_AIM "Script Exit"
# define SCRIPT_3_AIM "Script Frame"
# define SCRIPT_OBJ_AIM "Script obj"
# define SCRIPT_EMPTY "No script"
# define SCRIPT_EXT ".bmml"

typedef struct			s_editor_interface
{
	TTF_Font			*font;
	t_libui_widget		editor_container;
	t_libui_widget		save_textbutton;
	t_libui_widget		new_textbutton;
	t_libui_widget		light_textbutton;
	t_libui_widget		goal_textbutton;
	t_libui_widget		physics_textbutton;
	t_libui_widget		skybox_textbutton;
	t_libui_widget		portail_textbutton;
	t_libui_widget		secteur_selec_label;
	t_libui_widget		secteur_selec_up_button;
	t_libui_widget		secteur_selec_down_button;
	int32_t				secteur_courant;
	t_libui_widget		secteur2_selec_label;
	t_libui_widget		secteur2_selec_up_button;
	t_libui_widget		secteur2_selec_down_button;
	int32_t				secteur2_courant;
	t_libui_widget		lux_type_label;
	t_libui_widget		lux_type_change_button;
	enum e_light_type	lux_type;
	t_libui_widget		lux_inten_selec_label;
	t_libui_widget		lux_inten_selec_up_button;
	t_libui_widget		lux_inten_selec_up10_button;
	t_libui_widget		lux_inten_selec_down_button;
	t_libui_widget		lux_inten_selec_down10_button;
	double				lux_intensity;
	t_libui_widget		lux_fallof_selec_label;
	t_libui_widget		lux_fallof_selec_up_button;
	t_libui_widget		lux_fallof_selec_up_dot1_button;
	t_libui_widget		lux_fallof_selec_down_button;
	t_libui_widget		lux_fallof_selec_down_dot1_button;
	double				lux_fallof;
	t_libui_widget		select_container;
	t_libui_widget		select_label;
	t_libui_widget		selected_file_label;
	t_libui_widget		preview_container;
	t_libui_widget		view_container;
	t_libui_widget		label_physics_gravity;
	t_libui_widget		slider_physics_gravity_x;
	t_libui_widget		label_physics_gravity_x;
	t_libui_widget		label_nb_physics_gravity_x;
	t_libui_widget		up_button_physics_gravity_x;
	t_libui_widget		down_button_physics_gravity_x;
	t_libui_widget		slider_physics_gravity_y;
	t_libui_widget		label_physics_gravity_y;
	t_libui_widget		label_nb_physics_gravity_y;
	t_libui_widget		up_button_physics_gravity_y;
	t_libui_widget		down_button_physics_gravity_y;
	t_libui_widget		slider_physics_gravity_z;
	t_libui_widget		label_physics_gravity_z;
	t_libui_widget		label_nb_physics_gravity_z;
	t_libui_widget		up_button_physics_gravity_z;
	t_libui_widget		down_button_physics_gravity_z;
	t_libui_widget		label_physics_gbl_fric;
	t_libui_widget		slider_physics_gbl_fric_x;
	t_libui_widget		label_physics_gbl_fric_x;
	t_libui_widget		label_nb_physics_gbl_fric_x;
	t_libui_widget		up_button_physics_gbl_fric_x;
	t_libui_widget		down_button_physics_gbl_fric_x;
	t_libui_widget		slider_physics_gbl_fric_y;
	t_libui_widget		label_physics_gbl_fric_y;
	t_libui_widget		label_nb_physics_gbl_fric_y;
	t_libui_widget		up_button_physics_gbl_fric_y;
	t_libui_widget		down_button_physics_gbl_fric_y;
	t_libui_widget		slider_physics_gbl_fric_z;
	t_libui_widget		label_physics_gbl_fric_z;
	t_libui_widget		label_nb_physics_gbl_fric_z;
	t_libui_widget		up_button_physics_gbl_fric_z;
	t_libui_widget		down_button_physics_gbl_fric_z;
	t_libui_widget		label_physics_drag;
	t_libui_widget		slider_physics_drag_x;
	t_libui_widget		label_physics_drag_x;
	t_libui_widget		label_nb_physics_drag_x;
	t_libui_widget		up_button_physics_drag_x;
	t_libui_widget		down_button_physics_drag_x;
	t_libui_widget		slider_physics_drag_y;
	t_libui_widget		label_physics_drag_y;
	t_libui_widget		label_nb_physics_drag_y;
	t_libui_widget		up_button_physics_drag_y;
	t_libui_widget		down_button_physics_drag_y;
	t_libui_widget		slider_physics_drag_z;
	t_libui_widget		label_physics_drag_z;
	t_libui_widget		label_nb_physics_drag_z;
	t_libui_widget		up_button_physics_drag_z;
	t_libui_widget		down_button_physics_drag_z;
	t_libui_widget		slider_title_alpha;
	t_libui_widget		slider_alpha;
	t_libui_widget		label_alpha;
	t_libui_widget		label_nb_alpha;
	t_libui_widget		input_save_file;
	t_libui_widget		button_wall_friction;
	t_libui_widget		slider_physics_wall_friction;
	t_libui_widget		label_nb_physics_wall_friction;
	t_libui_widget		up_button_physics_wall_f;
	t_libui_widget		down_button_physics_wall_f;
	char				save_file_name[20];

	t_libui_widget		label_script_1_aim;
	t_libui_widget		label_script_1_file;
	t_libui_widget		area_script_1;
	t_libui_widget		button_disconnect_script_1;
	t_libui_widget		label_script_2_aim;
	t_libui_widget		label_script_2_file;
	t_libui_widget		area_script_2;
	t_libui_widget		button_disconnect_script_2;
	t_libui_widget		label_script_3_aim;
	t_libui_widget		label_script_3_file;
	t_libui_widget		area_script_3;
	t_libui_widget		button_disconnect_script_3;
	char				*script_1_path;
	char				*script_2_path;
	char				*script_3_path;
	SDL_Rect			script_1_area;
	SDL_Rect			script_2_area;
	SDL_Rect			script_3_area;

	t_libui_widget		label_script_obj_aim;
	t_libui_widget		label_script_obj_file;
	t_libui_widget		area_script_obj;
	t_libui_widget		button_disconnect_script_obj;
	SDL_Rect			script_obj_area;
	char				*script_obj_path;
	char				script_obj_name[12];

	t_mat4d				preview_mat;
	t_mat4d				item_mat;
	t_mat4d				item_scale_mat;
	t_vec4d				item_rotation;
	t_camera			editor_cam;
	t_bool				is_making_portail;
	t_bool				is_light;
	t_bool				is_physics;
	t_bool				is_goal;
	t_obj				*obj;
	t_mesh				*item_placer;
	t_bool				is_in_view;
	t_bool				is_modified;
	t_mesh				*selected_mesh;
	int					alpha;
	t_vec3d				sector_gravity;
	t_vec3d				sector_global_friction;
	t_vec3d				sector_drag;
	double				sector_speed_limit;
	double				dist;
	SDL_bool			wall_friction_is_auto;
	double				wall_friction;
	char				*path;
}						t_editor_interface;

struct					s_double_value_slider
{
	double				*value;
	t_libui_widget		*label;
};

struct					s_int_value_slider
{
	int					*value;
	t_libui_widget		*label;
};
# include "doom_nukem.h"


/*
** PREVIEW FUNCS
*/
void					render_preview(t_mesh *mesh, SDL_Surface *surf,
									t_vec2i size);
void					render_editor_view(t_world *world,
									t_editor_interface *ei);

/*
** Gestion secteur courant
*/
void					update_secteur_courant_text(t_libui_widget *label,
												unsigned int new_value);
int						increase_secteur_number(SDL_Event *event,
											t_libui_widget *widget, void *data);
int						decrease_secteur_number(SDL_Event *event,
											t_libui_widget *widget, void *data);

void					update_secteur2_courant_text(t_libui_widget *label,
												unsigned int new_value);
int						increase_secteur2_number(SDL_Event *event,
											t_libui_widget *widget, void *data);
int						decrease_secteur2_number(SDL_Event *event,
											t_libui_widget *widget, void *data);

/*
** Modification des sliders
*/
void					update_double_slider_data(t_libui_widget *slider,
									t_libui_widget *label, double new_value);

/*
** Gestion lumiere
*/

int						change_lux_type(SDL_Event *event,
										t_libui_widget *widget, void *data);
void					update_lux_inten_text(t_libui_widget *label,
									unsigned int new_value);
int						increase_lux_inten_number(SDL_Event *event,
											t_libui_widget *widget, void *data);
int						increase10_lux_inten_number(SDL_Event *event,
											t_libui_widget *widget, void *data);
int						decrease_lux_inten_number(SDL_Event *event,
											t_libui_widget *widget, void *data);
int						decrease10_lux_inten_number(SDL_Event *event,
											t_libui_widget *widget, void *data);

void					update_lux_intensity_text(t_libui_widget *label,
												double new_value);

int						increase_lux_fallof_number(SDL_Event *event,
											t_libui_widget *widget, void *data);
int						increasedot1_lux_fallof_number(SDL_Event *event,
											t_libui_widget *widget, void *data);
int						decrease_lux_fallof_number(SDL_Event *event,
											t_libui_widget *widget, void *data);
int						decreasedot1_lux_fallof_number(SDL_Event *event,
											t_libui_widget *widget, void *data);

void					update_lux_fallof_text(t_libui_widget *label,
											double new_value);

int						bf_switch_light(SDL_Event *event,
											t_libui_widget *widget, void *data);

void					update_lux_type_text(t_libui_widget *widget,
							enum e_light_type lux_type);

/*
** View functions
*/
void					remplir_3dview(t_editor_interface *editor_interface,
									t_e *e);
void					remplir_preview(t_editor_interface *editor_interface);

/*
** Gestion mode
*/
int						portail_pressed(SDL_Event *event,
										t_libui_widget *widget, void *data);

/*
** Editor boucle
*/
int						toggle_capture_mouse(SDL_Event *event,
										t_libui_widget *widget, void *data);
int						editor_event(t_e *e);
int						editor_update(t_e *e,
									t_editor_interface *editor_interface);
void					editor_render(t_e *e, t_libui_widgets_surface *ws,
								t_editor_interface *editor_interface);

/*
** SKYBOX
*/
int						bf_set_skybox(SDL_Event *event, t_libui_widget *widget,
							void *data);

/*
** PHYSICS
*/

int						bf_switch_physics(SDL_Event *event,
											t_libui_widget *widget, void *data);

int						bf_switch_goal(SDL_Event *event, t_libui_widget *widget,
							void *data);

void					update_sector_physics(t_e *e);

/*
** Addition of elements
*/
int						add_container_area(t_libui_widgets_surface *ws,
										t_editor_interface *editor_interface);
int						save_callback(SDL_Event *event,
									t_libui_widget *widget, void *user_data);
int						add_save_area(t_libui_widgets_surface *ws,
										t_editor_interface *editor_interface);
int						add_basic_entity_choice(t_libui_widgets_surface *ws,
								t_editor_interface *editor_interface, t_e *e);
int						add_selector_area(t_libui_widgets_surface *ws,
										t_editor_interface *editor_interface);
int						add_secteur_selector(t_libui_widgets_surface *ws,
								t_editor_interface *editor_interface, t_e *e);

int						add_secteur2_selector(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface, t_e *e);
int						add_lux_type_selector(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);

int						add_lux_inten_selector(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);
int						add_lux_fallof_selector(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);

int						add_physics_button(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);
int						add_preview_area(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);
int						add_view_area(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);

int						add_sliders_physics_gravity(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);
int						add_sliders_physics_gbl_fric(
						t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);
int						add_sliders_physics_drag(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);
int						add_slider_alpha(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);

int						add_save_file_input(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);
int						add_precision_slider_physics_gravity_up(
			t_libui_widgets_surface *ws, t_editor_interface *editor_interface);
int						add_precision_slider_physics_drag_up(
			t_libui_widgets_surface *ws, t_editor_interface *editor_interface);
int						add_precision_slider_physics_friction_up(
			t_libui_widgets_surface *ws, t_editor_interface *editor_interface);
int						add_precision_slider_physics_gravity_down(
			t_libui_widgets_surface *ws, t_editor_interface *editor_interface);
int						add_precision_slider_physics_drag_down(
			t_libui_widgets_surface *ws, t_editor_interface *editor_interface);
int						add_precision_slider_physics_friction_down(
			t_libui_widgets_surface *ws, t_editor_interface *editor_interface);

int						add_wall_friction(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);
int						add_precision_wall_friction(t_libui_widgets_surface *ws,
						t_editor_interface *editor_interface);

int						add_script_area(t_libui_widgets_surface *ws,
						t_editor_interface *edi);

int						create_script_obj_area(t_libui_widgets_surface *ws,
						t_editor_interface *edi);

int						add_delete_button(t_libui_widgets_surface *ws,
						t_editor_interface *edi, t_libui_widget *area_script, t_libui_widget *button);

/*
** Free
*/
void					free_editor_interface(t_editor_interface *editor_interface);

/*
** Update
*/
void					doom_dtoa(double value, char *text, unsigned int len);
int						slider_on_press_label_update(SDL_Event *event,
											t_libui_widget *widget, void *data);
int						slider_on_press_label_update2(SDL_Event *event,
											t_libui_widget *widget, void *data);
void				update_editor_interface_secteur(t_e *e,
						t_editor_interface	*edi);

/*
** Init
*/
int						init_editor(t_e *e, t_libui_widgets_surface *ws,
										t_editor_interface *editor_interface);
void					editor_init_value1(t_e *e, t_libui_widgets_surface *ws,
										t_editor_interface *editor_interface);
void					editor_init_value2(t_editor_interface *editor_interface);

/*
** Update supplementaire
*/

void					update_wall_friction(t_editor_interface *edi);
void					update_sector_friction(t_editor_interface *edi);
void					update_sector_drag(t_editor_interface *edi);
void					update_sector_gravity(t_editor_interface *edi);
void					update_alpha(t_editor_interface *edi);
void					update_is_goal(t_editor_interface *edi);
void					update_is_physics(t_editor_interface *edi);
void					update_is_light(t_editor_interface *edi);
void					update_is_making_portal(t_editor_interface *edi);
void					update_save_file_name(t_editor_interface *edi);

void					modifier_update_editor(t_mesh *mesh, t_editor_interface *editor);

#endif
