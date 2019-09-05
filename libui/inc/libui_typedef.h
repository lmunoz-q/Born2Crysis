/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_typedef.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:38:24 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/29 22:28:14 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_TYPEDEF_H
# define LIBUI_TYPEDEF_H

# include <SDL2/SDL.h>

typedef struct s_libui_env						t_libui_env;
typedef struct s_libui_keybind					t_libui_keybind;
typedef struct s_libui_thread					t_libui_thread;
typedef struct s_libui_window					t_libui_window;
typedef struct s_libui_window_constructor		t_libui_window_constructor;
typedef struct s_libui_widget					t_libui_widget;
typedef enum e_libui_widget_type				t_libui_widget_type;
typedef enum e_libui_widget_add_flags			t_libui_widget_add_flags;
typedef struct s_libui_widgets_surface			t_libui_widgets_surface;
typedef struct s_libui_widget_animation			t_libui_widget_animation;
typedef struct s_libui_widget_text				t_libui_widget_text;
typedef struct s_libui_widget_progressbar		t_libui_widget_progressbar;
typedef struct s_libui_widget_checkbox			t_libui_widget_checkbox;
typedef struct s_libui_widget_radio				t_libui_widget_radio;
typedef struct s_libui_inputtext				t_libui_inputtext;
typedef struct s_libui_widget_menu				t_libui_widget_menu;
typedef enum e_libui_widget_slider_freedom		t_libui_widget_slider_freedom;
typedef struct s_libui_textbutton_constructor	t_libui_textbutton_constructor;
typedef struct s_libui_inputtext_constructor	t_libui_inputtext_constructor;
typedef struct s_libui_menu_constructor			t_libui_menu_constructor;
typedef struct s_libui_double_color				t_libui_double_color;
typedef struct s_libui_callback_holder			t_libui_callback_holder;
typedef int										(t_libui_callback)(
														SDL_Event *event,
														t_libui_widget *widget,
														void *user_data);
typedef void									(t_libui_key_callback)(
														t_libui_widget *widget,
														char *key);
typedef void									(t_libui_callback_menu)
												(t_libui_widget*, char*, void*);
typedef struct s_libui_animation				t_libui_animation;
typedef int										(t_libui_animation_callback)(
														SDL_Texture *texture,
														size_t frame,
														void *user_data);
typedef struct s_int2							t_libui_pixel_coord;
typedef union u_libui_pixel_color				t_libui_pixel_color;
typedef struct s_libui_pixel					t_libui_pixel;

#endif
