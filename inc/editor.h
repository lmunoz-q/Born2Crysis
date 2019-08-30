/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 18:35:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/30 16:02:33 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "graphics.h"
# include "utilities.h"
# include "lights.h"
# include "libui.h"

#define EDITOR_MENU_WIDTH 500

#define FLY_SPEED			0.3
#define ROTATE_SPEED		1.0/180.0
#define MAX_SECTEURS 500 // defini le numero maximum du secteur selectionnable
#define SECTEUR_TEXT "Secteur courant: "
#define SECTEUR2_TEXT "Secteur secondaire: "
#define LUX_TYPE_TEXT "Lumiere type: " // 14
#define LUX_TYPE_POINT_TEXT "point"
#define LUX_TYPE_DIRECTION_TEXT "direction" // 9
#define SECTEUR_TEXT_SIZE 25

#define MAX_LUX_INTENSITY 25000.0
#define MAX_FALLOF_INTENSITY 25000.0
#define LUX_INTEN_TEXT "Intensite: "
#define LUX_FALLOF_TEXT "FallOf: "
#define LUX_TEXT_SIZE 25

typedef struct s_editor_interface
{
	TTF_Font		*font;

	t_libui_widget  editor_container;
	t_libui_widget	save_textbutton;
	t_libui_widget	new_textbutton;
	t_libui_widget	light_textbutton;
	t_libui_widget	goal_textbutton;
	t_libui_widget	physics_textbutton;
	t_libui_widget	skybox_textbutton;
	t_libui_widget  portail_textbutton;

	t_libui_widget secteur_selec_label;
	t_libui_widget secteur_selec_up_button;
	t_libui_widget secteur_selec_down_button;
	int32_t   		secteur_courant;

	t_libui_widget secteur2_selec_label;
	t_libui_widget secteur2_selec_up_button;
	t_libui_widget secteur2_selec_down_button;
	int32_t		   secteur2_courant;

	t_libui_widget			   lux_type_label;
	t_libui_widget			   lux_type_change_button;
	enum e_light_type		   lux_type;

	t_libui_widget lux_inten_selec_label;
	t_libui_widget lux_inten_selec_up_button;
	t_libui_widget lux_inten_selec_up10_button;
	t_libui_widget lux_inten_selec_down_button;
	t_libui_widget lux_inten_selec_down10_button;
	double   lux_intensity;

	t_libui_widget lux_fallof_selec_label;
	t_libui_widget lux_fallof_selec_up_button;
	t_libui_widget lux_fallof_selec_upDot1_button;
	t_libui_widget lux_fallof_selec_down_button;
	t_libui_widget lux_fallof_selec_downDot1_button;
	double   lux_fallof;

	t_libui_widget	select_container;
	t_libui_widget	select_label;
	t_libui_widget	selected_file_label;

	t_libui_widget	preview_container;
	t_libui_widget	view_container;

	t_libui_widget label_physics_gravity;
	t_libui_widget slider_physics_gravity_x;
	t_libui_widget label_physics_gravity_x;
	t_libui_widget labelNB_physics_gravity_x;
	t_libui_widget slider_physics_gravity_y;
	t_libui_widget label_physics_gravity_y;
	t_libui_widget labelNB_physics_gravity_y;
	t_libui_widget slider_physics_gravity_z;
	t_libui_widget label_physics_gravity_z;
	t_libui_widget labelNB_physics_gravity_z;

	t_libui_widget label_physics_gbl_fric;
	t_libui_widget slider_physics_gbl_fric_x;
	t_libui_widget label_physics_gbl_fric_x;
	t_libui_widget labelNB_physics_gbl_fric_x;
	t_libui_widget slider_physics_gbl_fric_y;
	t_libui_widget label_physics_gbl_fric_y;
	t_libui_widget labelNB_physics_gbl_fric_y;
	t_libui_widget slider_physics_gbl_fric_z;
	t_libui_widget label_physics_gbl_fric_z;
	t_libui_widget labelNB_physics_gbl_fric_z;

	t_libui_widget label_physics_drag;
	t_libui_widget slider_physics_drag_x;
	t_libui_widget label_physics_drag_x;
	t_libui_widget labelNB_physics_drag_x;
	t_libui_widget slider_physics_drag_y;
	t_libui_widget label_physics_drag_y;
	t_libui_widget labelNB_physics_drag_y;
	t_libui_widget slider_physics_drag_z;
	t_libui_widget label_physics_drag_z;
	t_libui_widget labelNB_physics_drag_z;

	t_libui_widget slider_title_alpha;
	t_libui_widget slider_alpha;
	t_libui_widget label_alpha;
	t_libui_widget labelNB_alpha;

	t_libui_widget	input_save_file;

	char			save_file_name[20];

	t_mat4d			preview_mat;
	t_mat4d			item_mat;
	t_mat4d			item_scale_mat;
	// t_mat4d			item_rotation_mat;
	t_vec4d			item_rotation;

	t_camera		editor_cam;

	t_bool			is_making_portail;
	t_bool			is_light;
	t_bool			is_physics;
	t_bool			is_goal;

	t_obj			*obj;
	t_mesh			*item_placer;
	t_bool			is_in_view;
	t_mesh			*selected_mesh;

	int				alpha;
	t_vec3d			sector_gravity;
	t_vec3d			sector_global_friction;
	t_vec3d			sector_drag;
	double			sector_speed_limit;
	double			dist;
} t_editor_interface;

struct s_double_value_slider
{
	double			*value;
	t_libui_widget	*label;
};

struct s_int_value_slider
{
	int				*value;
	t_libui_widget	*label;
};

# include "doom_nukem.h"

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
int  decrease_secteur_number(SDL_Event *event, t_libui_widget *widget,
							 void *data);

void update_secteur2_courant_text(t_libui_widget *label, unsigned int new_value);
int  increase_secteur2_number(SDL_Event *event, t_libui_widget *widget,
							 void *data);
int  decrease_secteur2_number(SDL_Event *event, t_libui_widget *widget,
							 void *data);

/*
** Modification des sliders
*/
void	update_double_slider_data(t_libui_widget *slider, t_libui_widget *label, double new_value);


/*
** Gestion lumiere
*/

int change_lux_type(SDL_Event *event, t_libui_widget *widget, void *data);
void update_lux_inten_text(t_libui_widget *label,
								  unsigned int	new_value);
int  increase_lux_inten_number(SDL_Event *event, t_libui_widget *widget,
							   void *data);
int  increase10_lux_inten_number(SDL_Event *event, t_libui_widget *widget,
							   void *data);
int  decrease_lux_inten_number(SDL_Event *event, t_libui_widget *widget,
							   void *data);
int  decrease10_lux_inten_number(SDL_Event *event, t_libui_widget *widget,
							   void *data);

void update_lux_intensity_text(t_libui_widget *label, double new_value);

int increase_lux_fallof_number(SDL_Event *event, t_libui_widget *widget,
							   void *data);
int increasedot1_lux_fallof_number(SDL_Event *event, t_libui_widget *widget,
							   void *data);
int decrease_lux_fallof_number(SDL_Event *event, t_libui_widget *widget,
							   void *data);
int decreasedot1_lux_fallof_number(SDL_Event *event, t_libui_widget *widget,
							   void *data);

void update_lux_fallof_text(t_libui_widget *label, double new_value);

int		bf_switch_light(SDL_Event *event, t_libui_widget *widget,
							void *data);

/*
** View functions
*/
void remplir_3dview(t_editor_interface *editor_interface, t_e *e);
void remplir_preview(t_editor_interface *editor_interface, t_e *e);


/*
** Gestion mode
*/
int portail_pressed(SDL_Event *event, t_libui_widget *widget, void *data);

/*
** Editor boucle
*/
int toggle_capture_mouse(SDL_Event *event, t_libui_widget *widget,
							 void *data);
int editor_event(t_e *e, t_libui_widgets_surface *ws,
								 t_editor_interface *editor_interface);
int editor_update(t_e *e, t_libui_widgets_surface *ws,
				  				t_editor_interface *editor_interface);
void editor_render(t_e *e, t_libui_widgets_surface *ws,
				   t_editor_interface *editor_interface);


/*
** SKYBOX
*/
int		bf_set_skybox(SDL_Event *event, t_libui_widget *widget,
							void *data);

/*
** PHYSICS
*/

int		bf_switch_physics(SDL_Event *event, t_libui_widget *widget,
							void *data);

int		bf_switch_goal(SDL_Event *event, t_libui_widget *widget,
							void *data);

void    update_sector_physics(t_e *e);

/*
** Addition of elements
*/
int add_container_area(t_libui_widgets_surface *ws, t_editor_interface *editor_interface);
int	save_callback(SDL_Event *event, t_libui_widget *widget, void *user_data);
int add_save_area(t_libui_widgets_surface *ws, t_editor_interface *editor_interface);
int	add_basic_entity_choice(t_libui_widgets_surface *ws, t_editor_interface *editor_interface, t_e * e);
int	add_selector_area(t_libui_widgets_surface *ws, t_editor_interface *	 editor_interface);
int add_secteur_selector(t_libui_widgets_surface *ws,
						 t_editor_interface *	 editor_interface, t_e *e);

int add_secteur2_selector(t_libui_widgets_surface *ws,
						 t_editor_interface *	 editor_interface, t_e *e);
int add_lux_type_selector(t_libui_widgets_surface *ws,
						  t_editor_interface *	 editor_interface);

int add_lux_inten_selector(t_libui_widgets_surface *ws,
						  t_editor_interface *	 editor_interface);
int add_lux_fallof_selector(t_libui_widgets_surface *ws,
						t_editor_interface *		editor_interface);

int add_physics_button(t_libui_widgets_surface *ws,
					 t_editor_interface *editor_interface);
int add_preview_area(t_libui_widgets_surface *ws,
					 t_editor_interface *editor_interface);
int add_view_area(t_libui_widgets_surface *ws,
				  t_editor_interface *editor_interface, t_e *e);

int add_sliders_physics_gravity(t_libui_widgets_surface *ws,
							t_editor_interface *	 editor_interface);
int			add_sliders_physics_gbl_fric(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface);

int			add_sliders_physics_drag(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface);
int add_slider_alpha(t_libui_widgets_surface *ws,
					 t_editor_interface *	 editor_interface);

int	add_save_file_input(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface);

/*
** Free
*/
void	free_editor_interface(t_editor_interface *editor_interface);

/*
** Update
*/
void		remplir_preview(t_editor_interface *editor_interface, t_e *e);
void		remplir_3dview(t_editor_interface *editor_interface, t_e *e);
int	slider_on_press_label_update(SDL_Event *event, t_libui_widget *widget, void *data);
int slider_on_press_label_update2(SDL_Event *event, t_libui_widget *widget,
									  void *data);

/*
** Init
*/
int init_editor(t_e *e, t_libui_widgets_surface *ws,
				 t_editor_interface		*editor_interface);
void	editor_init_value1(t_e *e, t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface);
void	editor_init_value2(t_editor_interface *editor_interface);
#endif
