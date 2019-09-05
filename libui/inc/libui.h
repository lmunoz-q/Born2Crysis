/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:31:32 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/29 22:29:47 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_H
# define LIBUI_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>

# include <libui_animation.h>
# include <libui_callback.h>
# include <libui_env.h>
# include <libui_maths.h>
# include <libui_pixel.h>
# include <libui_surface.h>
# include <libui_text.h>
# include <libui_threads.h>
# include <libui_typedef.h>
# include <libui_widgets.h>
# include <libui_widgets_templates.h>
# include <libui_window.h>

/*
** some hotkeys/scroll/behaviors:
** vertical/horizontal scroll / up (not focus) / down (not focus) = if the view
**   is bigger than the window, change
** the center of the window in the view and update side scrollbars
** shift + vertical scroll / right (not focus) / left (not focus) = horizontal
**   scroll
** ctrl + vertical scroll = zoom
** home / command + up = got to the top of the view
** end / command + down = go to the end of the view
** page up/down / alt + up/down = jump a full vertical window size in the view
** shift + page up/down / alt + right/left= jump a full horizontal window size
**   in the view
** ctrl + tab / ctrl + page down = got to next tab/view
** ctrl + shift + tab / ctrl + page up = got to previous tab/view
** tab = go to next composite
** shift + tab = go to previous composite
*/

int						libui_init(void);
void					libui_close(void);
int						libui_process_events(SDL_Event *event);

/*
** ----- Widget creation ------------------------------------------------------
**
** --- For each widget you can fullfill this basic ----------------------------
** Creation of the widget
** Modification of his properties (Visuals, callback, default values)
** Addition to the parent (all the members of the surface are child or
**		grandchild of the surface composite)
** Recuperation an modification of his values
** Deletion of widget
** ----------------------------------------------------------------------------
*/

/*
** ----------------------------------------------------------------------------
** --- Container widget
** ----------------------------------------------------------------------------
*/

/*
** Widget
** Shared properties of widget
** is_hidden
*/

void					libui_widget_destroy(t_libui_widget *widget);
void					libui_widget_set_pos(t_libui_widget *widget,
											SDL_Point point);

/*
** Composite
** A rectangle that can contain widget
** Optional background (if background, it can be a color or a image)
** (if texture use 9patch format)
*/

int						libui_create_container(t_libui_widget *widget,
												SDL_Rect rect, int color);

/*
** Progress Bar
** A rectangle that show a progress
** It can use color or textures (if texture use something like 9patch format)
** - Setter on the value of the progress
*/

void					libui_redraw_progressbar_texture(
														t_libui_widget *widget);
int						libui_create_progressbar(t_libui_widget *widget,
												SDL_Rect rect);
void					libui_progressbar_set_current_value(
										t_libui_widget *widget, int new_value);
void					libui_progressbar_set_minmax_value(
				t_libui_widget *widget, int new_min_value, int new_max_value);
void					libui_progressbar_set_colors(t_libui_widget *widget,
										int new_backcolor, int new_frontcolor);
int						libui_progressbar_get_current_value(
														t_libui_widget *widget);
int						libui_progressbar_get_max_value(t_libui_widget *widget);
int						libui_progressbar_get_min_value(t_libui_widget *widget);

/*
** Image
** A rectangle with an image inside
** the image can have an alpha channel
** - Setter on the texture of the image
*/

int						libui_create_image(t_libui_widget *widget, char *path,
											SDL_Rect rect);
int						libui_image_set_texture(t_libui_widget *widget,
												char *path);

/*
** Label
** A rectangle wich contain text
** The rectangle is hidden by default
** - Setter on the value of the text
*/

void					libui_redraw_label_texture(t_libui_widget *widget);
int						libui_create_label(t_libui_widget *widget,
									SDL_Rect size, char *text, TTF_Font *font);
void					libui_label_set_text(t_libui_widget *widget,
											char *text);
char					*libui_label_get_text(t_libui_widget *widget);
void					libui_label_set_color(t_libui_widget *widget,
												SDL_Color color);

/*
** /!\ Destroy_label_data don't free the font /!\
** This behavior was chosen to allow multiple labels to share the same font
*/

void					libui_destroy_label_data(t_libui_widget_text *data);

/*
** Bouton
** A clickable area
** Focusable
** Can contain child (mostly used child: Text and Image)
** A callback on click
*/

int						libui_create_button(t_libui_widget *widget,
											SDL_Rect rect, int color);

/*
** Text button
** A composition of widget that function as a button with text
**
** create also add it to the surface
*/

int						libui_create_textbutton(t_libui_widget *widget,
								t_libui_textbutton_constructor *constructor);
void					libui_init_textbutton_constructor(
								t_libui_textbutton_constructor *constructor);

/*
** Slider
** A composition of widget that function as a slider
*/

int						libui_create_slider(t_libui_widget *widget,
										SDL_Rect rect, SDL_bool with_cursor);
void					libui_slider_update(t_libui_widget *widget);

/*
** Menu
** A menu that open a list of textbutton
**
** create also add it to the surface
*/

void					libui_init_menu_constructor(
										t_libui_menu_constructor *constructor);
int						libui_create_menu(t_libui_widget *widget,
										t_libui_menu_constructor *constructor);
t_libui_callback_holder	*libui_menu_add_option(t_libui_widget *widget,
												char *text, TTF_Font *font);

/*
** InputText
*/

void					libui_init_inputtext_constructor(
								t_libui_inputtext_constructor *constructor);
int						libui_create_inputtext(t_libui_widget *widget,
									t_libui_inputtext_constructor *constructor);
void					libui_destroy_inputtext_data(t_libui_widget *widget);

/*
** Event Handles
*/

int						handle_pressed_event(SDL_Event *event,
										t_libui_window *win, t_libui_widget *w);
int						handle_hover_event(SDL_Event *event,
								t_libui_widgets_surface *ws, t_libui_widget *w);
int						handle_keydown_event(SDL_Event *event,
											t_libui_window *win);

#endif
