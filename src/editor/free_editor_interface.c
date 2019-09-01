/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_editor_interface.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:15:40 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/01 18:15:38 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

static void	free_editor_interface_sub1(t_editor_interface *editor_interface)
{
	libui_widget_destroy(&editor_interface->editor_container);
	libui_widget_destroy(&editor_interface->save_textbutton);
	libui_widget_destroy(&editor_interface->new_textbutton);
	libui_widget_destroy(&editor_interface->light_textbutton);
	libui_widget_destroy(&editor_interface->goal_textbutton);
	libui_widget_destroy(&editor_interface->physics_textbutton);
	libui_widget_destroy(&editor_interface->skybox_textbutton);
	libui_widget_destroy(&editor_interface->portail_textbutton);
	libui_widget_destroy(&editor_interface->secteur_selec_label);
	libui_widget_destroy(&editor_interface->secteur_selec_up_button);
	libui_widget_destroy(&editor_interface->secteur_selec_down_button);
	libui_widget_destroy(&editor_interface->secteur2_selec_label);
	libui_widget_destroy(&editor_interface->secteur2_selec_up_button);
	libui_widget_destroy(&editor_interface->secteur2_selec_down_button);
	libui_widget_destroy(&editor_interface->lux_type_label);
	libui_widget_destroy(&editor_interface->lux_type_change_button);
	libui_widget_destroy(&editor_interface->lux_inten_selec_label);
	libui_widget_destroy(&editor_interface->lux_inten_selec_up_button);
	libui_widget_destroy(&editor_interface->lux_inten_selec_up10_button);
	libui_widget_destroy(&editor_interface->lux_inten_selec_down_button);
	libui_widget_destroy(&editor_interface->lux_inten_selec_down10_button);
}

static void	free_editor_interface_sub2(t_editor_interface *editor_interface)
{
	libui_widget_destroy(&editor_interface->lux_fallof_selec_label);
	libui_widget_destroy(&editor_interface->lux_fallof_selec_up_button);
	libui_widget_destroy(&editor_interface->lux_fallof_selec_up_dot1_button);
	libui_widget_destroy(&editor_interface->lux_fallof_selec_down_button);
	libui_widget_destroy(&editor_interface->lux_fallof_selec_down_dot1_button);
	libui_widget_destroy(&editor_interface->select_container);
	libui_widget_destroy(&editor_interface->select_label);
	libui_widget_destroy(&editor_interface->selected_file_label);
	libui_widget_destroy(&editor_interface->preview_container);
	libui_widget_destroy(&editor_interface->view_container);
	libui_widget_destroy(&editor_interface->label_physics_gravity);
	libui_widget_destroy(&editor_interface->slider_physics_gravity_x);
	libui_widget_destroy(&editor_interface->label_physics_gravity_x);
	libui_widget_destroy(&editor_interface->label_nb_physics_gravity_x);
	libui_widget_destroy(&editor_interface->slider_physics_gravity_y);
	libui_widget_destroy(&editor_interface->label_physics_gravity_y);
	libui_widget_destroy(&editor_interface->label_nb_physics_gravity_y);
	libui_widget_destroy(&editor_interface->slider_physics_gravity_z);
	libui_widget_destroy(&editor_interface->label_physics_gravity_z);
	libui_widget_destroy(&editor_interface->label_nb_physics_gravity_z);
}

static void	free_editor_interface_sub3(t_editor_interface *editor_interface)
{
	libui_widget_destroy(&editor_interface->label_physics_gbl_fric);
	libui_widget_destroy(&editor_interface->slider_physics_gbl_fric_x);
	libui_widget_destroy(&editor_interface->label_physics_gbl_fric_x);
	libui_widget_destroy(&editor_interface->label_nb_physics_gbl_fric_x);
	libui_widget_destroy(&editor_interface->slider_physics_gbl_fric_y);
	libui_widget_destroy(&editor_interface->label_physics_gbl_fric_y);
	libui_widget_destroy(&editor_interface->label_nb_physics_gbl_fric_y);
	libui_widget_destroy(&editor_interface->slider_physics_gbl_fric_z);
	libui_widget_destroy(&editor_interface->label_physics_gbl_fric_z);
	libui_widget_destroy(&editor_interface->label_nb_physics_gbl_fric_z);
	libui_widget_destroy(&editor_interface->label_physics_drag);
	libui_widget_destroy(&editor_interface->slider_physics_drag_x);
	libui_widget_destroy(&editor_interface->label_physics_drag_x);
	libui_widget_destroy(&editor_interface->label_nb_physics_drag_x);
	libui_widget_destroy(&editor_interface->slider_physics_drag_y);
	libui_widget_destroy(&editor_interface->label_physics_drag_y);
	libui_widget_destroy(&editor_interface->label_nb_physics_drag_y);
	libui_widget_destroy(&editor_interface->slider_physics_drag_z);
	libui_widget_destroy(&editor_interface->label_physics_drag_z);
	libui_widget_destroy(&editor_interface->label_nb_physics_drag_z);
}

static void	free_editor_interface_sub4(t_editor_interface *editor_interface)
{
	libui_widget_destroy(&editor_interface->slider_title_alpha);
	libui_widget_destroy(&editor_interface->slider_alpha);
	libui_widget_destroy(&editor_interface->label_alpha);
	libui_widget_destroy(&editor_interface->label_nb_alpha);
	libui_widget_destroy(&editor_interface->input_save_file);
	libui_widget_destroy(&editor_interface->up_button_physics_gravity_x);
	libui_widget_destroy(&editor_interface->up_button_physics_gravity_y);
	libui_widget_destroy(&editor_interface->up_button_physics_gravity_z);
	libui_widget_destroy(&editor_interface->button_wall_friction);
	libui_widget_destroy(&editor_interface->slider_physics_wall_friction);
	libui_widget_destroy(&editor_interface->label_nb_physics_wall_friction);
	libui_widget_destroy(&editor_interface->up_button_physics_wall_f);
	libui_widget_destroy(&editor_interface->down_button_physics_wall_f);
}

void		free_editor_interface(t_editor_interface *editor_interface)
{
	free_editor_interface_sub1(editor_interface);
	free_editor_interface_sub2(editor_interface);
	free_editor_interface_sub3(editor_interface);
	free_editor_interface_sub4(editor_interface);
}
