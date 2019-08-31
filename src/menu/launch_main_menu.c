/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_main_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:41:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/21 16:13:01 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom_nukem.h"
#include "menu.h"
#include <SDL2/SDL.h>

void	launch_main_menu(t_e *e)
{
	t_libui_widgets_surface		ws;
	t_libui_widget				widget_buttonplay;
	t_libui_widget				widget_labelplay;
	t_libui_widget				widget_buttoneditor;
	t_libui_widget				widget_labeleditor;
	t_libui_widget				widget_buttonquitter;
	t_libui_widget				widget_labelquitter;
	TTF_Font					*font;
	SDL_Event					event;
	SDL_bool					win_running;
	SDL_bool					editor_running;
	SDL_bool					game_running;
	t_double_color				theme;

	theme.second_color = 0xff999999;
	theme.first_color = 0xffcccccc;
	libui_widgets_new_widgets_surface(
		(SDL_Rect){0, 0, LUI_DEAULT_WINDOW_WIDTH, LUI_DEFAULT_WINDOW_HEIGHT},
		&ws);
	e->win->widgets_surface = &ws;
	e->win->refresh_rate = 60;
	font = TTF_OpenFont("./libui/resources/Prototype.ttf", 64);
	game_running = SDL_FALSE;
	editor_running = SDL_FALSE;
	if (font == NULL)
		printf("Unable to load the font\n");
	else
	{
		add_quitbutton(e, &widget_buttonquitter, &widget_labelquitter, font,
			&theme, &win_running);
		add_editorbutton(e, &widget_buttoneditor, &widget_labeleditor, font,
			&theme, &editor_running);
		add_playbutton(e, &widget_buttonplay, &widget_labelplay, font, &theme,
			&game_running);
	}
	win_running = SDL_TRUE;
	while (win_running)
	{
		if (libui_process_events(&event))
		{
			if (event.type == SDL_QUIT
				|| (event.type == SDL_KEYDOWN
					&& event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				break ;
		}
		if (libui_window_process_fps(e->win))
		{
			libui_window_clear_atomic(e->win);
			libui_widgets_draw(&ws);
			SDL_BlitSurface(ws.surface, NULL, e->win->surface, NULL);
			libui_window_refresh(e->win);
			libui_window_title(e->win, "fps: %d", e->win->fps);
		}
		if (game_running == SDL_TRUE)
		{
			free(ws.pixel_bound_widget);
			SDL_FreeSurface(ws.surface);
			libui_widgets_new_widgets_surface(
				(SDL_Rect){0, 0, LUI_DEAULT_WINDOW_WIDTH,
					LUI_DEFAULT_WINDOW_HEIGHT},
				&ws);
			libui_window_clear_atomic(e->win);
			libui_widgets_draw(&ws);
			SDL_BlitSurface(ws.surface, NULL, e->win->surface, NULL);
			libui_window_refresh(e->win);
			init_game_state(e);
			run_game(e);
			win_running = SDL_FALSE;
		}
		if (editor_running == SDL_TRUE)
		{
			free(ws.pixel_bound_widget);
			SDL_FreeSurface(ws.surface);
			libui_widgets_new_widgets_surface(
				(SDL_Rect){0, 0, LUI_DEAULT_WINDOW_WIDTH,
					LUI_DEFAULT_WINDOW_HEIGHT},
				&ws);
			libui_window_clear_atomic(e->win);
			libui_widgets_draw(&ws);
			SDL_BlitSurface(ws.surface, NULL, e->win->surface, NULL);
			libui_window_refresh(e->win);
			launch_editor_interface(e);
			win_running = SDL_FALSE;
		}
	}
	TTF_CloseFont(font);
	libui_widget_destroy(&widget_buttonplay);
	libui_widget_destroy(&widget_labelplay);
	libui_widget_destroy(&widget_buttoneditor);
	libui_widget_destroy(&widget_labeleditor);
	libui_widget_destroy(&widget_buttonquitter);
	libui_widget_destroy(&widget_labelquitter);
}
