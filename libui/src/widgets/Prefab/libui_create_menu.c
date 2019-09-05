/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_create_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 23:24:57 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:40:33 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int			menu_parent_on_pressed(SDL_Event *event,
											t_libui_widget *widget, void *data)
{
	(void)event;
	(void)widget;
	if (((t_libui_widget_menu *)data)->unselecteur.is_hiden)
		libui_widget_set_visibility(
			&((t_libui_widget_menu *)data)->unselecteur, 1, 1, 0);
	return (0);
}

static int			menu_unselected(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	(void)event;
	(void)widget;
	if (!((t_libui_widget_menu *)data)->unselecteur.is_hiden)
		libui_widget_set_visibility(
			&((t_libui_widget_menu *)data)->unselecteur, 0, 1, 0);
	return (0);
}

static inline void	i_0(t_libui_widget *widget, t_libui_menu_constructor *c,
	t_libui_widget_menu *data, t_libui_widget *widget_label)
{
	if (c->ws != NULL)
	{
		data->ws.next = c->ws->next;
		if (c->ws->next != NULL)
			c->ws->next->previous = &data->ws;
		data->ws.previous = c->ws;
		c->ws->next = &data->ws;
	}
	libui_widgets_add_widget(&data->ws, &data->unselecteur, 0, NULL);
	libui_widgets_add_widget(&data->ws, &data->selecteur, 0,
							&data->unselecteur);
	libui_callback_sethover(widget, libui_callback_hoverbutton,
							SDL_MOUSEMOTION, (void *)(c->theme));
	libui_callback_setpressed(widget, menu_parent_on_pressed,
							SDL_MOUSEBUTTONDOWN, data);
	libui_callback_setpressed(&data->unselecteur, menu_unselected,
							SDL_MOUSEBUTTONDOWN, data);
	libui_widgets_add_widget(c->ws, widget, 0, c->parent);
	libui_widgets_add_widget(c->ws, widget_label, 0, widget);
	libui_widget_set_visibility(&data->unselecteur, 0, 1, 0);
}

int					libui_create_menu(t_libui_widget *widget,
	t_libui_menu_constructor *c)
{
	t_libui_widget			*widget_label;
	t_libui_widget_menu		*data;

	if (!libui_create_button(widget, c->rect, 0xffaaaaaa))
		return (0);
	widget->type = LUI_WT_MENU;
	free(widget->data);
	data = (t_libui_widget_menu *)calloc(1, sizeof(t_libui_widget_menu));
	widget->data = data;
	if (widget->data == NULL)
		return (0);
	data->option_height = c->option_height;
	widget_label = (t_libui_widget *)malloc(sizeof(t_libui_widget));
	if (!libui_create_label(widget_label, c->label_rect, c->text, c->font))
		return (0);
	data->selecteur = libui_widgets_templates_null();
	data->unselecteur = libui_widgets_templates_null();
	libui_widgets_new_widgets_surface((SDL_Rect){0, 0, c->ws->surface->w,
												c->ws->surface->h}, &data->ws);
	c->selecteur_rect.h = c->options_number * data->option_height;
	libui_create_container(&data->selecteur, c->selecteur_rect, 0xffaaaaaa);
	libui_create_button(&data->unselecteur, (SDL_Rect){0, 0,
						data->ws.surface->w, data->ws.surface->h}, 0x90aaaaaa);
	i_0(widget, c, data, widget_label);
	return (0);
}
