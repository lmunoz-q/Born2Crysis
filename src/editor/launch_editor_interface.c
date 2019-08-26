/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_editor_interface.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:41:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/26 15:57:34 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom_nukem.h"

int add_container_area(t_libui_widgets_surface *ws, t_editor_interface *editor_interface)
{
	if (!libui_create_container(
			&(editor_interface->editor_container),
			(SDL_Rect){.x = ws->surface->w - EDITOR_MENU_WIDTH,
					   .y = 0,
					   .w = EDITOR_MENU_WIDTH,
					   .h = ws->surface->h},
			0xff444444))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->editor_container), 0,
							 NULL);
	return (0);
}

int	save_callback(SDL_Event *event, t_libui_widget *widget, void *user_data)
{
	t_map_file	*data;
	SDL_RWops	*io;

	(void)user_data;
	(void)event;
	(void)widget;
	io = SDL_RWFromFile("test.b2cm", "wb");
	if ((data = world_to_map_file(get_world())) == NULL)
		return (0);
	SDL_RWwrite(io, data, 1, data->total_size);
	SDL_free(data);
	SDL_RWclose(io);
	return (0);
}

int add_save_area(t_libui_widgets_surface *ws, t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor	cons;

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 10, .y = 10, .w = 50, .h = 50};
	cons.rect
		= (SDL_Rect){.x = EDITOR_MENU_WIDTH - 50, .y = 10, .w = 50, .h = 50};
	cons.text = "Save";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->save_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Save.\n");
		return (1);
	}
	cons.rect
		= (SDL_Rect){.x = EDITOR_MENU_WIDTH - 50, .y = 70, .w = 50, .h = 50};
	cons.text = "New";
	if (libui_create_textbutton(&(editor_interface->new_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton New.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->save_textbutton), save_callback, SDL_MOUSEBUTTONDOWN, NULL);
	return (0);
}

int	add_basic_entity_choice(t_libui_widgets_surface *ws, t_editor_interface *editor_interface, t_e * e)
{
	t_libui_textbutton_constructor cons;

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 10, .y = 10, .w = 100, .h = 50};
	cons.rect
		= (SDL_Rect){.x = 10, .y = 415, .w = 150, .h = 50};
	cons.text = "LIGHT (OFF)";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->light_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Wall.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->light_textbutton), bf_switch_light, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons.rect
		= (SDL_Rect){.x = EDITOR_MENU_WIDTH - 80, .y = 260, .w = 80, .h = 50};
	cons.text = "SKYBOX";
	if (libui_create_textbutton(&(editor_interface->skybox_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Obj.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->skybox_textbutton), bf_set_skybox, SDL_MOUSEBUTTONDOWN, e);
	cons.rect
		= (SDL_Rect){.x = EDITOR_MENU_WIDTH - 80, .y = 320, .w = 80, .h = 50};
	cons.text = "MESH";
	editor_interface->is_making_portail = FALSE;
	if (libui_create_textbutton(&(editor_interface->portail_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Port.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->portail_textbutton), portail_pressed, SDL_MOUSEBUTTONDOWN, editor_interface);
	return (0);
}

int	add_selector_area(t_libui_widgets_surface *ws,
				  t_editor_interface *	 editor_interface)
{
	if (!libui_create_container(
			&(editor_interface->select_container),
			(SDL_Rect){.x = 0,
					   .y = ws->surface->h - 100,
					   .w = EDITOR_MENU_WIDTH,
					   .h = 100},
			0xffaaaaaa))
		return (1);
	if (!libui_create_label(
			&(editor_interface->selected_file_label),
			(SDL_Rect){.x = 10, .y = 75, .w = EDITOR_MENU_WIDTH - 20, .h = 20},
			"\"No file selected\"", editor_interface->font))
		return (1);
	if (!libui_create_label(
			&(editor_interface->select_label),
			(SDL_Rect){.x = 10, .y = 10, .w = EDITOR_MENU_WIDTH - 20, .h = 20},
			"File selector", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->select_container), 0,
							 &(editor_interface->editor_container));
	libui_widgets_add_widget(ws, &(editor_interface->selected_file_label), 0,
							 &(editor_interface->select_container));
	libui_widgets_add_widget(ws, &(editor_interface->select_label), 0,
							 &(editor_interface->select_container));
	return (0);
}

int add_secteur_selector(t_libui_widgets_surface *ws,
						 t_editor_interface *	 editor_interface, t_e *e)
{
	t_libui_textbutton_constructor cons;
	t_libui_callback			callback;

	if (!libui_create_label(
			&(editor_interface->secteur_selec_label),
			(SDL_Rect){
				.x = 40, .y = 325, .w = 175, .h = 20},
			"Secteur courant: 0", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->secteur_selec_label), 0,
							 &(editor_interface->editor_container));

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 8, .y = 5, .w = 30, .h = 30};
	cons.rect
		= (SDL_Rect){.x = 10, .y = 320, .w = 30, .h = 30};
	cons.text = "-1";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->secteur_selec_down_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton -1.\n");
		return (1);
	}
	libui_callback_setpressed(
		&(editor_interface->secteur_selec_down_button), decrease_secteur_number,
		SDL_MOUSEBUTTONDOWN, editor_interface);
	cons.rect = (SDL_Rect){.x = 215, .y = 320, .w = 30, .h = 30};
	cons.text = "+1";
	if (libui_create_textbutton(&(editor_interface->secteur_selec_up_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton +1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->secteur_selec_up_button),
							  increase_secteur_number, SDL_MOUSEBUTTONDOWN,
							  e);
	editor_interface->secteur_courant = 0;
	return (0);
}

int add_secteur2_selector(t_libui_widgets_surface *ws,
						 t_editor_interface *	 editor_interface, t_e *e)
{
	t_libui_textbutton_constructor cons;
	t_libui_callback			   callback;

	if (!libui_create_label(&(editor_interface->secteur2_selec_label),
							(SDL_Rect){.x = 40, .y = 365, .w = 195, .h = 20},
							"Secteur secondaire: 0", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->secteur2_selec_label), 0,
							 &(editor_interface->editor_container));

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 8, .y = 5, .w = 30, .h = 30};
	cons.rect = (SDL_Rect){.x = 10, .y = 360, .w = 30, .h = 30};
	cons.text = "-1";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->secteur2_selec_down_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton -1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->secteur2_selec_down_button),
							  decrease_secteur2_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	cons.rect = (SDL_Rect){.x = 235, .y = 360, .w = 30, .h = 30};
	cons.text = "+1";
	if (libui_create_textbutton(&(editor_interface->secteur2_selec_up_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton +1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->secteur2_selec_up_button),
							  increase_secteur2_number, SDL_MOUSEBUTTONDOWN,
							  e);
	editor_interface->secteur2_courant = 0;
	return (0);
}

int add_lux_type_selector(t_libui_widgets_surface *ws,
						  t_editor_interface *	 editor_interface)
{
	t_libui_textbutton_constructor cons;
	t_libui_callback			   callback;

	if (!libui_create_label(&(editor_interface->lux_type_label),
							(SDL_Rect){.x = 40, .y = 480, .w = 215, .h = 20},
							"Lumiere type: point", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->lux_type_label), 0,
							 &(editor_interface->editor_container));

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 7, .y = 5, .w = 30, .h = 30};
	cons.rect = (SDL_Rect){.x = 10, .y = 475, .w = 30, .h = 30};
	cons.text = "<>";
	cons.ws = ws;
	if (libui_create_textbutton(&(editor_interface->lux_type_change_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton <>.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_type_change_button),
							  change_lux_type, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	editor_interface->lux_type = POINT_LIGHT;
	return (0);
}

int add_lux_inten_selector(t_libui_widgets_surface *ws,
						  t_editor_interface *	 editor_interface)
{
	t_libui_textbutton_constructor cons;
	t_libui_callback			   callback;

	if (!libui_create_label(&(editor_interface->lux_inten_selec_label),
							(SDL_Rect){.x = 80, .y = 520, .w = 195, .h = 20},
							"Intensite: 1", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->lux_inten_selec_label), 0,
							 &(editor_interface->editor_container));

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 7, .y = 5, .w = 50, .h = 30};
	cons.rect = (SDL_Rect){.x = 50, .y = 515, .w = 30, .h = 30};
	cons.text = "-1";
	cons.ws = ws;
	if (libui_create_textbutton(
			&(editor_interface->lux_inten_selec_down_button), &cons))
	{
		printf("Error lors de la creation du textbouton -1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_inten_selec_down_button),
							  decrease_lux_inten_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	cons.rect = (SDL_Rect){.x = 275, .y = 515, .w = 30, .h = 30};
	cons.text = "+1";
	if (libui_create_textbutton(&(editor_interface->lux_inten_selec_up_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton +1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_inten_selec_up_button),
							  increase_lux_inten_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	cons.rect = (SDL_Rect){.x = 310, .y = 515, .w = 45, .h = 30};
	cons.text = "+10";
	if (libui_create_textbutton(&(editor_interface->lux_inten_selec_up10_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton +10.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_inten_selec_up10_button),
							  increase10_lux_inten_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	cons.rect = (SDL_Rect){.x = 10, .y = 515, .w = 35, .h = 30};
	cons.text = "-10";
	if (libui_create_textbutton(
			&(editor_interface->lux_inten_selec_down10_button), &cons))
	{
		printf("Error lors de la creation du textbouton -10.\n");
		return (1);
	}
	libui_callback_setpressed(
		&(editor_interface->lux_inten_selec_down10_button),
		decrease10_lux_inten_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	editor_interface->lux_intensity = 1.0;
	return (0);
}

int add_lux_fallof_selector(t_libui_widgets_surface *ws,
						   t_editor_interface *		editor_interface)
{
	t_libui_textbutton_constructor cons;
	t_libui_callback			   callback;

	if (!libui_create_label(&(editor_interface->lux_fallof_selec_label),
							(SDL_Rect){.x = 80, .y = 560, .w = 195, .h = 20},
							"FallOf: 1", editor_interface->font))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->lux_fallof_selec_label), 0,
							 &(editor_interface->editor_container));

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 7, .y = 5, .w = 50, .h = 30};
	cons.rect = (SDL_Rect){.x = 50, .y = 555, .w = 30, .h = 30};
	cons.text = "-1";
	cons.ws = ws;
	if (libui_create_textbutton(
			&(editor_interface->lux_fallof_selec_down_button), &cons))
	{
		printf("Error lors de la creation du textbouton -1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_fallof_selec_down_button),
							  decrease_lux_fallof_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	cons.rect = (SDL_Rect){.x = 275, .y = 555, .w = 30, .h = 30};
	cons.text = "+1";
	if (libui_create_textbutton(&(editor_interface->lux_fallof_selec_up_button),
								&cons))
	{
		printf("Error lors de la creation du textbouton +1.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->lux_fallof_selec_up_button),
							  increase_lux_fallof_number, SDL_MOUSEBUTTONDOWN,
							  editor_interface);
	cons.rect = (SDL_Rect){.x = 310, .y = 555, .w = 45, .h = 30};
	cons.text = "+0.1";
	if (libui_create_textbutton(
			&(editor_interface->lux_fallof_selec_upDot1_button), &cons))
	{
		printf("Error lors de la creation du textbouton +0.1.\n");
		return (1);
	}
	libui_callback_setpressed(
		&(editor_interface->lux_fallof_selec_upDot1_button),
		increaseDot1_lux_fallof_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	cons.rect = (SDL_Rect){.x = 10, .y = 555, .w = 35, .h = 30};
	cons.text = "-0.1";
	if (libui_create_textbutton(
			&(editor_interface->lux_fallof_selec_downDot1_button), &cons))
	{
		printf("Error lors de la creation du textbouton -0.1.\n");
		return (1);
	}
	libui_callback_setpressed(
		&(editor_interface->lux_fallof_selec_downDot1_button),
		decreaseDot1_lux_fallof_number, SDL_MOUSEBUTTONDOWN, editor_interface);
	editor_interface->lux_fallof = 1.0;
	return (0);
}

int add_physics_button(t_libui_widgets_surface *ws,
					 t_editor_interface *editor_interface)
{
	t_libui_textbutton_constructor cons;

	libui_init_textbutton_constructor(&cons);
	cons.parent = &(editor_interface->editor_container);
	cons.font = editor_interface->font;
	cons.label_rect = (SDL_Rect){.x = 10, .y = 10, .w = 120, .h = 50};
	cons.rect
		= (SDL_Rect){.x = 10, .y = 610, .w = 150, .h = 50};
	cons.text = "PHYSICS (OFF)";
	cons.ws = ws;
	editor_interface->is_physics = FALSE;
	if (libui_create_textbutton(&(editor_interface->physics_textbutton), &cons))
	{
		printf("Error lors de la creation du textbouton Wall.\n");
		return (1);
	}
	libui_callback_setpressed(&(editor_interface->physics_textbutton), bf_switch_physics, SDL_MOUSEBUTTONDOWN, editor_interface);
	return (0);
}

int add_preview_area(t_libui_widgets_surface *ws,
					 t_editor_interface *editor_interface)
{
	if (!libui_create_container(&(editor_interface->preview_container),
								(SDL_Rect){.x = 0,
										   .y = 10,
										   .w = EDITOR_MENU_WIDTH - 100,
										   .h = 300},
								0xffaaaaaa))
		return (1);
	libui_widgets_add_widget(ws, &(editor_interface->preview_container), 0,
							 &(editor_interface->editor_container));
	return (0);
}

int add_view_area(t_libui_widgets_surface *ws,
				  t_editor_interface *editor_interface, t_e *e)
{
	(void)e;
	if (!libui_create_container(&(editor_interface->view_container),
								(SDL_Rect){.x = 0,
										   .y = 0,
										   .w = ws->surface->w - EDITOR_MENU_WIDTH,
										   .h = ws->surface->h},
								0xffaaaaaa))
		return (1);
	//libui_callback_setpressed(&(editor_interface->view_container),
						//	  toggle_capture_mouse, SDL_MOUSEBUTTONDOWN,
						//	  e->win->ptr);
	libui_widgets_add_widget(ws, &(editor_interface->view_container), 0,
							NULL);
	return (0);
}

void	free_editor_interface(t_editor_interface *editor_interface)
{
	(void)editor_interface;
}

void remplir_preview(t_editor_interface *editor_interface, t_e *e)
{
	t_mat4d		mat4_tmp;
	
	(void)e;
	gthread_get(GTHREAD_PREVIEW);
	if (editor_interface->item_placer)
	{
		mat4_tmp = ((t_mesh *)editor_interface->item_placer)->matrix;
		((t_mesh *)editor_interface->item_placer)->matrix = editor_interface->preview_mat;
		render_preview(editor_interface->item_placer, editor_interface->preview_container.texture,
		(t_vec2i){.a = {editor_interface->preview_container.texture->w, editor_interface->preview_container.texture->h}});
		((t_mesh *)editor_interface->item_placer)->matrix = mat4_tmp;
		editor_interface->preview_container.need_redraw = 1;
	}
}

void remplir_3dview(t_editor_interface *editor_interface, t_e *e)
{
	t_vec3d		tmp;
	double		new_radius;
	int			i;
	int			y;
	t_mat4d		m;

	gthread_get(GTHREAD_EDITOR);
	editor_interface->view_container.need_redraw = 1;
	render_editor_view(&e->world, editor_interface);
	mat4_init(&editor_interface->item_mat);
	if (!editor_interface->item_placer)
		return ;
	editor_interface->item_placer->matrix = editor_interface->item_scale_mat;
	new_radius = get_mesh_radius(editor_interface->item_placer) + 15;
	tmp = vec3vec3_substract(editor_interface->editor_cam.pos,
	vec3scalar_multiply(editor_interface->editor_cam.view_dir, (new_radius > 15) ? new_radius : 15));
	m = quat_to_mat4d(editor_interface->item_rotation);
	editor_interface->item_placer->matrix = mat4mat4_multiply(((t_mesh *)editor_interface->item_placer)->matrix , m);
	editor_interface->item_placer->matrix = mat4_translate(((t_mesh *)editor_interface->item_placer)->matrix, tmp.n.x, tmp.n.y, tmp.n.z);
	render_mesh(editor_interface->item_placer, &editor_interface->editor_cam, editor_interface->view_container.texture, NULL);
	i = editor_interface->view_container.texture->w / 2 - 5;
	y = editor_interface->view_container.texture->h / 2;
	while (i < editor_interface->view_container.texture->w / 2 + 5)
	{
		((int *)(editor_interface->view_container.texture->pixels))[y * editor_interface->view_container.texture->w + i] = 0xffffffff;
		i++;
	}
	i = editor_interface->view_container.texture->w / 2;
	y = editor_interface->view_container.texture->h / 2 - 5;
	while (y < editor_interface->view_container.texture->h / 2 + 5)
	{
		((int *)(editor_interface->view_container.texture
			->pixels))[y * editor_interface->view_container.texture->w + i]
			= 0xffffffff;
		y++;
	}
}





/*
** ----------------------------------------------------------------------------------------------------------
** Slider hell
*/
static void doom_dtoa_sub(char *text, int nb)
{
	int tmp;
	int	i;

	tmp = nb;
	i = 0;
	while (tmp >= 10)
	{
		tmp = tmp / 10;
		i++;
	}
	while (i >= 0)
	{
		text[i] = '0' + nb % 10;
		nb = nb / 10;
		i--;
	}
}
void 	doom_str_clean(char *text, unsigned int len)
{
	unsigned int nb;

	nb = 0;
	while (nb < len)
	{
		text[nb] = '\0';
		nb++;
	}
}

static void doom_dtoa(double value, char *text, unsigned int len)
{
	unsigned int	nb;

	doom_str_clean(text, len);
	nb = (int)value;
	doom_dtoa_sub(text, nb);
	while(*text != '\0')
		++text;
	*text = '.';
	++text;
	nb = (int)((value - (double)nb) * (double)100);
	doom_dtoa_sub(text, nb);
}

static int	slider_on_pressLabelUpdate(SDL_Event *event, t_libui_widget *widget, void *data)
{
	t_libui_widget_slider *slider;
	int					   tmp_x;
	char				   tmp_text[25];
	struct s_double_value_slider	*dvs;

	(void) event;
	dvs = (struct s_double_value_slider*)data;
	if (widget->type == LUI_WT_SLIDER)
	{
		slider = (t_libui_widget_slider *)widget->data;
		SDL_GetMouseState(&tmp_x, NULL);
		tmp_x = tmp_x - widget->rect.x;
		if (tmp_x > widget->rect.w)
			tmp_x = widget->rect.w;
		if (widget->rect.w == 0)
			return (-1);
		tmp_x = (double)(tmp_x) / (double)widget->rect.w
				* (double)(slider->progressbardata->value_max
							- slider->progressbardata->value_min);
		libui_progressbar_set_current_value(widget, tmp_x);
		doom_dtoa((double)tmp_x / (double)100.0, tmp_text, 25);
		*(dvs->value) = (double)tmp_x / (double)100.0;
		libui_label_set_text(dvs->label, tmp_text);
		libui_slider_update(widget);
	}
	return (0);
}

static int slider_on_pressLabelUpdate2(SDL_Event *event, t_libui_widget *widget,
									  void *data)
{
	t_libui_widget_slider *		  slider;
	int							  tmp_x;
	char						  tmp_text[25];
	struct s_int_value_slider *ivs;

	(void)event;
	ivs = (struct s_int_value_slider *)data;
	if (widget->type == LUI_WT_SLIDER)
	{
		slider = (t_libui_widget_slider *)widget->data;
		SDL_GetMouseState(&tmp_x, NULL);
		tmp_x = tmp_x - widget->rect.x;
		if (tmp_x > widget->rect.w)
			tmp_x = widget->rect.w;
		if (widget->rect.w == 0)
			return (-1);
		tmp_x = (double)(tmp_x) / (double)widget->rect.w
				* (double)(slider->progressbardata->value_max
						   - slider->progressbardata->value_min);
		libui_progressbar_set_current_value(widget, tmp_x);
		doom_str_clean(tmp_text, 25);
		doom_dtoa_sub(tmp_text, tmp_x);
		*(ivs->value) = tmp_x;
		libui_label_set_text(ivs->label, tmp_text);
		libui_slider_update(widget);
	}
	return (0);
}

int add_sliders_physics_gravity(t_libui_widgets_surface *ws,
							t_editor_interface *	 editor_interface)
{
	static struct s_double_value_slider dvs_x;
	static struct s_double_value_slider dvs_y;
	static struct s_double_value_slider dvs_z;

	if (!libui_create_label(&editor_interface->label_physics_gravity,
							(SDL_Rect){2, 678, 160, 20}, "Gravity",
							editor_interface->font))
		return (-1);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gravity, 0,
							 &editor_interface->editor_container);
	/* X ------------------------------------------------------ */
	if (!libui_create_slider(&editor_interface->slider_physics_gravity_x,
							 (SDL_Rect){20, 700, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_gravity_x, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_gravity_x, 0);
	if (!libui_create_label(&editor_interface->label_physics_gravity_x,
							(SDL_Rect){2, 700, 16, 20}, "x:",
							editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_gravity_x,
							(SDL_Rect){122, 700, 40, 20}, "0",
							editor_interface->font))
		return (-1);
	dvs_x.value = &(editor_interface->sector_gravity.n.x);
	dvs_x.label = &editor_interface->labelNB_physics_gravity_x;
	libui_callback_setpressed(&editor_interface->slider_physics_gravity_x,
							  slider_on_pressLabelUpdate, SDL_MOUSEBUTTONDOWN,
							  &dvs_x);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gravity_x,
							 0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_gravity_x,
							 0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_gravity_x, 0,
							 &editor_interface->editor_container);
	/* Y ------------------------------------------------------ */
	if (!libui_create_slider(&editor_interface->slider_physics_gravity_y,
							 (SDL_Rect){20, 722, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_gravity_y, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_gravity_y, 0);
	if (!libui_create_label(&editor_interface->label_physics_gravity_y,
							(SDL_Rect){2, 722, 16, 20},
							"y:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_gravity_y,
							(SDL_Rect){122, 722, 40, 20}, "0",
							editor_interface->font))
		return (-1);
	dvs_y.value = &(editor_interface->sector_gravity.n.y);
	dvs_y.label = &editor_interface->labelNB_physics_gravity_y;
	libui_callback_setpressed(&editor_interface->slider_physics_gravity_y,
							  slider_on_pressLabelUpdate, SDL_MOUSEBUTTONDOWN,
							  &dvs_y);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gravity_y, 0,
							 &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_gravity_y,
							 0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_gravity_y, 0,
							 &editor_interface->editor_container);
	/* X ------------------------------------------------------ */
	if (!libui_create_slider(&editor_interface->slider_physics_gravity_z,
							 (SDL_Rect){20, 744, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_gravity_z, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_gravity_z, 0);
	if (!libui_create_label(&editor_interface->label_physics_gravity_z,
							(SDL_Rect){2, 744, 16, 20},
							"z:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_gravity_z,
							(SDL_Rect){122, 744, 40, 20}, "0",
							editor_interface->font))
		return (-1);
	dvs_z.value = &(editor_interface->sector_gravity.n.z);
	dvs_z.label = &editor_interface->labelNB_physics_gravity_z;
	libui_callback_setpressed(&editor_interface->slider_physics_gravity_z,
							  slider_on_pressLabelUpdate, SDL_MOUSEBUTTONDOWN,
							  &dvs_z);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gravity_z, 0,
							 &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_gravity_z,
							 0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_gravity_z, 0,
							 &editor_interface->editor_container);
	return (0);
}

int add_sliders_physics_gbl_fric(t_libui_widgets_surface *ws,
								t_editor_interface *	 editor_interface)
{
	static struct s_double_value_slider dvs_x;
	static struct s_double_value_slider dvs_y;
	static struct s_double_value_slider dvs_z;

	if (!libui_create_label(&editor_interface->label_physics_gbl_fric,
							(SDL_Rect){2, 768, 160, 20}, "Global Friction",
							editor_interface->font))
		return (-1);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gbl_fric, 0,
							 &editor_interface->editor_container);
	/* X ------------------------------------------------------ */
	if (!libui_create_slider(&editor_interface->slider_physics_gbl_fric_x,
							 (SDL_Rect){20, 790, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_gbl_fric_x, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_gbl_fric_x, 0);
	if (!libui_create_label(&editor_interface->label_physics_gbl_fric_x,
							(SDL_Rect){2, 790, 16, 20},
							"x:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_gbl_fric_x,
							(SDL_Rect){122, 790, 40, 20}, "0",
							editor_interface->font))
		return (-1);
	dvs_x.value = &(editor_interface->sector_global_friction.n.x);
	dvs_x.label = &editor_interface->labelNB_physics_gbl_fric_x;
	libui_callback_setpressed(&editor_interface->slider_physics_gbl_fric_x,
							  slider_on_pressLabelUpdate, SDL_MOUSEBUTTONDOWN,
							  &dvs_x);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gbl_fric_x, 0,
							 &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_gbl_fric_x,
							 0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_gbl_fric_x, 0,
							 &editor_interface->editor_container);
	/* Y ------------------------------------------------------ */
	if (!libui_create_slider(&editor_interface->slider_physics_gbl_fric_y,
							 (SDL_Rect){20, 812, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_gbl_fric_y, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_gbl_fric_y, 0);
	if (!libui_create_label(&editor_interface->label_physics_gbl_fric_y,
							(SDL_Rect){2, 812, 16, 20},
							"y:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_gbl_fric_y,
							(SDL_Rect){122, 812, 40, 20}, "0",
							editor_interface->font))
		return (-1);
	dvs_y.value = &(editor_interface->sector_global_friction.n.y);
	dvs_y.label = &editor_interface->labelNB_physics_gbl_fric_y;
	libui_callback_setpressed(&editor_interface->slider_physics_gbl_fric_y,
							  slider_on_pressLabelUpdate, SDL_MOUSEBUTTONDOWN,
							  &dvs_y);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gbl_fric_y, 0,
							 &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_gbl_fric_y,
							 0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_gbl_fric_y, 0,
							 &editor_interface->editor_container);
	/* X ------------------------------------------------------ */
	if (!libui_create_slider(&editor_interface->slider_physics_gbl_fric_z,
							 (SDL_Rect){20, 834, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_gbl_fric_z, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_gbl_fric_z, 0);
	if (!libui_create_label(&editor_interface->label_physics_gbl_fric_z,
							(SDL_Rect){2, 834, 16, 20},
							"z:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_gbl_fric_z,
							(SDL_Rect){122, 834, 40, 20}, "0",
							editor_interface->font))
		return (-1);
	dvs_z.value = &(editor_interface->sector_global_friction.n.z);
	dvs_z.label = &editor_interface->labelNB_physics_gbl_fric_z;
	libui_callback_setpressed(&editor_interface->slider_physics_gbl_fric_z,
							  slider_on_pressLabelUpdate, SDL_MOUSEBUTTONDOWN,
							  &dvs_z);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_gbl_fric_z, 0,
							 &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_gbl_fric_z,
							 0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_gbl_fric_z, 0,
							 &editor_interface->editor_container);
	return (0);
}

int add_sliders_physics_drag(t_libui_widgets_surface *ws,
								 t_editor_interface *	 editor_interface)
{
	static struct s_double_value_slider dvs_x;
	static struct s_double_value_slider dvs_y;
	static struct s_double_value_slider dvs_z;

	if (!libui_create_label(&editor_interface->label_physics_drag,
							(SDL_Rect){2, 858, 160, 20}, "Drag",
							editor_interface->font))
		return (-1);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_drag, 0,
							 &editor_interface->editor_container);
	/* X ------------------------------------------------------ */
	if (!libui_create_slider(&editor_interface->slider_physics_drag_x,
							 (SDL_Rect){20, 880, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_drag_x, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_drag_x, 0);
	if (!libui_create_label(&editor_interface->label_physics_drag_x,
							(SDL_Rect){2, 880, 16, 20},
							"x:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_drag_x,
							(SDL_Rect){122, 880, 40, 20}, "0",
							editor_interface->font))
		return (-1);
	dvs_x.value = &(editor_interface->sector_global_friction.n.x);
	dvs_x.label = &editor_interface->labelNB_physics_drag_x;
	libui_callback_setpressed(&editor_interface->slider_physics_drag_x,
							  slider_on_pressLabelUpdate, SDL_MOUSEBUTTONDOWN,
							  &dvs_x);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_drag_x, 0,
							 &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_drag_x,
							 0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_drag_x,
							 0, &editor_interface->editor_container);
	/* Y ------------------------------------------------------ */
	if (!libui_create_slider(&editor_interface->slider_physics_drag_y,
							 (SDL_Rect){20, 902, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_drag_y, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_drag_y, 0);
	if (!libui_create_label(&editor_interface->label_physics_drag_y,
							(SDL_Rect){2, 902, 16, 20},
							"y:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_drag_y,
							(SDL_Rect){122, 902, 40, 20}, "0",
							editor_interface->font))
		return (-1);
	dvs_y.value = &(editor_interface->sector_global_friction.n.y);
	dvs_y.label = &editor_interface->labelNB_physics_drag_y;
	libui_callback_setpressed(&editor_interface->slider_physics_drag_y,
							  slider_on_pressLabelUpdate, SDL_MOUSEBUTTONDOWN,
							  &dvs_y);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_drag_y, 0,
							 &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_drag_y,
							 0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_drag_y,
							 0, &editor_interface->editor_container);
	/* X ------------------------------------------------------ */
	if (!libui_create_slider(&editor_interface->slider_physics_drag_z,
							 (SDL_Rect){20, 924, 100, 20}, SDL_FALSE))
		return (1);
	libui_progressbar_set_minmax_value(
		&editor_interface->slider_physics_drag_z, 0, 100);
	libui_progressbar_set_current_value(
		&editor_interface->slider_physics_drag_z, 0);
	if (!libui_create_label(&editor_interface->label_physics_drag_z,
							(SDL_Rect){2, 924, 16, 20},
							"z:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_physics_drag_z,
							(SDL_Rect){122, 924, 40, 20}, "0",
							editor_interface->font))
		return (-1);
	dvs_z.value = &(editor_interface->sector_global_friction.n.z);
	dvs_z.label = &editor_interface->labelNB_physics_drag_z;
	libui_callback_setpressed(&editor_interface->slider_physics_drag_z,
							  slider_on_pressLabelUpdate, SDL_MOUSEBUTTONDOWN,
							  &dvs_z);
	libui_widgets_add_widget(ws, &editor_interface->label_physics_drag_z, 0,
							 &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_physics_drag_z,
							 0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_physics_drag_z,
							 0, &editor_interface->editor_container);
	return (0);
}

int add_slider_alpha(t_libui_widgets_surface *ws,
					 t_editor_interface *	 editor_interface)
{
	static struct s_int_value_slider ivs_a;

	if (!libui_create_label(&editor_interface->slider_title_alpha,
							(SDL_Rect){165, 678, 160, 20}, "Alpha",
							editor_interface->font))
		return (-1);
	libui_widgets_add_widget(ws, &editor_interface->slider_title_alpha, 0,
							&editor_interface->editor_container);
	/* X ------------------------------------------------------ */
	if (!libui_create_slider(&editor_interface->slider_alpha,
							(SDL_Rect){183, 700, 275, 20}, SDL_FALSE))
		return (-1);
	libui_progressbar_set_minmax_value(&editor_interface->slider_alpha, 0, 256);
	libui_progressbar_set_current_value(&editor_interface->slider_alpha, 0);
	if (!libui_create_label(&editor_interface->label_alpha,
							(SDL_Rect){165, 700, 16, 20},
							"a:", editor_interface->font))
		return (-1);
	if (!libui_create_label(&editor_interface->labelNB_alpha,
							(SDL_Rect){460, 700, 40, 20}, "0",
							editor_interface->font))
		return (-1);
	ivs_a.value = &(editor_interface->alpha);
	ivs_a.label = &editor_interface->labelNB_alpha;
	libui_callback_setpressed(&editor_interface->slider_alpha,
							slider_on_pressLabelUpdate2, SDL_MOUSEBUTTONDOWN,
							&ivs_a);
	libui_widgets_add_widget(ws, &editor_interface->label_alpha, 0,
							 &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->labelNB_alpha,
							 0, &editor_interface->editor_container);
	libui_widgets_add_widget(ws, &editor_interface->slider_alpha, 0,
							 &editor_interface->editor_container);
return (0);
}

/**
** ---------------------------------------------------------------------------------------------------------
** Sorti du slider hell
*/

void init_editor(t_e *e, t_libui_widgets_surface *ws,
				 t_editor_interface		*editor_interface)
{
	libui_widgets_new_widgets_surface(
		(SDL_Rect){0, 0, LUI_DEAULT_WINDOW_WIDTH, LUI_DEFAULT_WINDOW_HEIGHT},
		ws);
	e->win->widgets_surface = ws;
	e->win->refresh_rate = 60;
	e->editor_running = TRUE;
	editor_interface->is_making_portail = 1;
	editor_interface->font = TTF_OpenFont("./libui/resources/Prototype.ttf", 16);
	init_default_editor_controls(&e->input_map, e);
	init_zbuff(ws->surface->h * ws->surface->w);
	if (editor_interface->font == NULL)
	{
		printf("Unable to load the font\n");
	}
	else
	{
		// TODO add all the parts

		if (add_container_area(ws, editor_interface))
			return; // TODO gerer une sortie sur erreur propre
		// add button save area
		if (add_save_area(ws, editor_interface))
			return; // TODO gerer une sortie sur erreur propre
		// add button select basic entity
		if (add_basic_entity_choice(ws, editor_interface, e))
			return; // TODO gerer une sortie sur erreur propre
		// add selector of file : drag and rop or select file modals
		if (add_selector_area(ws, editor_interface))
			return; // TODO gerer une sortie sur erreur propre
		// add choix secteur
		if (add_secteur_selector(ws, editor_interface, e))
			return;
		if (add_secteur2_selector(ws, editor_interface, e))
			return;
		if (add_lux_type_selector(ws, editor_interface))
			return;
		if (add_lux_inten_selector(ws, editor_interface))
			return;
		if (add_lux_fallof_selector(ws, editor_interface))
			return;
		if (add_physics_button(ws, editor_interface))
			return;
		if (add_sliders_physics_gravity(ws, editor_interface))
			return;
		if (add_sliders_physics_gbl_fric(ws, editor_interface))
			return;
		if (add_sliders_physics_drag(ws, editor_interface))
			return;
		if (add_slider_alpha(ws, editor_interface))
			return;
		// add recap control

		// add preview
		if (add_preview_area(ws, editor_interface))
			return;
		// add 3d view
		if (add_view_area(ws, editor_interface, e))
			return;
	}
	gthread_init(4, editor_interface->preview_container.texture,
				 get_polygon_buffer(), GTHREAD_PREVIEW);
	gthread_init(20, editor_interface->view_container.texture,
				 get_polygon_buffer(), GTHREAD_EDITOR);
	init_camera(&editor_interface->editor_cam,
				(t_vec2i){.n.x = editor_interface->view_container.texture->w,
						  .n.y = editor_interface->view_container.texture->h});
	mat4_init(&editor_interface->preview_mat);
	editor_interface->preview_mat = mat4_translate(editor_interface->preview_mat, 0, -10, 0);
	mat4_init(&editor_interface->item_mat);
	mat4_init(&editor_interface->item_scale_mat);
	// mat4_init(&editor_interface->item_rotation_mat);
	editor_interface->item_rotation = (t_vec4d){{0, 0, 0, 1}};
	editor_interface->is_in_view = FALSE;
	editor_interface->is_light = FALSE;
	editor_interface->item_placer = NULL;
	editor_interface->sector_gravity = (t_vec3d){.a = {0, -1.2, 0}};
	editor_interface->sector_global_friction = (t_vec3d){.a = {1, 1.0, 1}};
	editor_interface->sector_drag = (t_vec3d){.a = {0.95, 1, 0.95}};
	editor_interface->sector_speed_limit = 0.80;
	if (!e->world.sectors)
	{
		sector_create(&e->world);
		e->world.sectors[editor_interface->secteur_courant].physics.drag = editor_interface->sector_drag;
		e->world.sectors[editor_interface->secteur_courant].physics.gravity = editor_interface->sector_gravity;
		e->world.sectors[editor_interface->secteur_courant].physics.global_friction = editor_interface->sector_global_friction;
		e->world.sectors[editor_interface->secteur_courant].physics.speed_limit = editor_interface->sector_speed_limit;
	}
}

void close_editor(t_editor_interface *editor_interface)
{

	free_editor_interface(editor_interface);
	TTF_CloseFont(editor_interface->font);
}

void	launch_editor_interface(t_e *e)
{
	t_libui_widgets_surface		ws;
	uint32_t	last_frame;
	double		elapsed_time;
	uint32_t	tmp;

	init_editor(e, &ws, &e->editor);
	elapsed_time = 0;
	last_frame = SDL_GetTicks();
	while (e->editor_running)
	{             
		while (elapsed_time >= DELTATIME)
		{
			editor_event(e, &ws, &e->editor);
			editor_update(e, &ws, &e->editor);
			elapsed_time -= DELTATIME;
		}
		editor_render(e, &ws, &e->editor);
		tmp = SDL_GetTicks();
		elapsed_time += (double)(tmp - last_frame) / 1000.0;
		last_frame = tmp;
		count_fps(&e->stats.fps);
	}
	close_editor(&e->editor);
}
