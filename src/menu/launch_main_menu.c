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

int		change_color(SDL_Event *event, t_libui_widget *widget, void *data)
{
	SDL_Rect		rect_tmp;
	SDL_Cursor		*cursor;

	if (event->type == SDL_MOUSEMOTION)
	{
		rect_tmp.x = 0;
		rect_tmp.y = 0;
		rect_tmp.h = widget->rect.h;
		rect_tmp.w = widget->rect.w;
		if (widget->is_hover)
		{
			cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
			SDL_FillRect(widget->texture, &rect_tmp,
						((t_double_color *)data)->first_color);
		}
		else
		{
			cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
			SDL_FillRect(widget->texture, &rect_tmp,
						((t_double_color *)data)->second_color);
		}
		SDL_SetCursor(cursor);
		widget->need_redraw = 1;
	}
	return (1);
}

int		print_message(SDL_Event *event, t_libui_widget *widget, void *data)
{
	(void)event;
	(void)widget;
	printf("%s\n", (char *)data);
	return (0);
}

int		switch_bool(SDL_Event *event, t_libui_widget *widget, void *data)
{
	SDL_bool	*bl;

	(void)event;
	(void)widget;
	bl = (SDL_bool *)data;
	if (*bl == SDL_TRUE)
		*bl = SDL_FALSE;
	else
		*bl = SDL_TRUE;
	return (0);
}

int		add_quitbutton(t_e *e, t_libui_widget *widget_buttonquitter,
	t_libui_widget *widget_labelquitter, TTF_Font *font,
	t_double_color *theme, SDL_bool *running)
{
	SDL_Rect		size;

	size.x = 100;
	size.y = e->win->surface->h - 200;
	size.h = 100;
	size.w = e->win->surface->w - 200;
	if (!libui_create_button(widget_buttonquitter, size, 0xffaaaaaa))
	{
		printf("Unable to create the button\n");
		return (-1);
	}
	libui_widgets_add_widget(e->win->widgets_surface, widget_buttonquitter,
							0, NULL);
	widget_buttonquitter->on_hover.callback = change_color;
	widget_buttonquitter->on_hover.filter = SDL_MOUSEMOTION;
	widget_buttonquitter->on_hover.user_data = theme;
	widget_buttonquitter->on_hover.widget = widget_buttonquitter;
	widget_buttonquitter->on_press.callback = switch_bool;
	widget_buttonquitter->on_press.filter = SDL_MOUSEBUTTONDOWN;
	widget_buttonquitter->on_press.user_data = running;
	widget_buttonquitter->on_press.widget = widget_buttonquitter;
	// --- --- Label switch scene --- ---
	size.x = 10;
	size.y = 10;
	size.h = 80;
	size.w = e->win->surface->w - 200;
	if (!libui_create_label(widget_labelquitter, size, "Quitter", font))
	{
		printf("Unable to create the label\n");
		return (-1);
	}
	libui_widgets_add_widget(e->win->widgets_surface, widget_labelquitter, 0,
		widget_buttonquitter);
	return (0);
}

int		add_playbutton(t_e *e, t_libui_widget *widget_buttonplay,
	t_libui_widget *widget_labelplay, TTF_Font *font, t_double_color *theme,
	SDL_bool *running)
{
	SDL_Rect size;

	size.x = 100;
	size.y = e->win->surface->h - 450;
	size.h = 100;
	size.w = e->win->surface->w - 200;
	if (!libui_create_button(widget_buttonplay, size, 0xffaaaaaa))
	{
		printf("Unable to create the button\n");
		return (-1);
	}
	libui_widgets_add_widget(e->win->widgets_surface,
		widget_buttonplay, 0, NULL);
	widget_buttonplay->on_hover.callback = change_color;
	widget_buttonplay->on_hover.filter = SDL_MOUSEMOTION;
	widget_buttonplay->on_hover.user_data = theme;
	widget_buttonplay->on_hover.widget = widget_buttonplay;
	widget_buttonplay->on_press.callback = switch_bool;
	widget_buttonplay->on_press.filter = SDL_MOUSEBUTTONDOWN;
	widget_buttonplay->on_press.user_data = running;
	widget_buttonplay->on_press.widget = widget_buttonplay;
	// --- --- Label switch scene --- ---
	size.x = 10;
	size.y = 10;
	size.h = 80;
	size.w = e->win->surface->w - 200;
	if (!libui_create_label(widget_labelplay, size, "Jouer solo", font))
	{
		printf("Unable to create the label\n");
		return (-1);
	}
	libui_widgets_add_widget(e->win->widgets_surface,
		widget_labelplay, 0, widget_buttonplay);
	return (0);
}

int add_editorbutton(t_e *e, t_libui_widget *widget_buttoneditor,
				   t_libui_widget *widget_labeleditor, TTF_Font *font,
				   t_double_color *theme, SDL_bool *running)
{
	SDL_Rect size;

	size.x = 100;
	size.y = e->win->surface->h - 325;
	size.h = 100;
	size.w = e->win->surface->w - 200;
	if (!libui_create_button(widget_buttoneditor, size, 0xffaaaaaa))
	{
		printf("Unable to create the button\n");
		return (-1);
	}
	libui_widgets_add_widget(e->win->widgets_surface, widget_buttoneditor, 0,
							 NULL);

	widget_buttoneditor->on_hover.callback = change_color;
	widget_buttoneditor->on_hover.filter = SDL_MOUSEMOTION;
	widget_buttoneditor->on_hover.user_data = theme;
	widget_buttoneditor->on_hover.widget = widget_buttoneditor;

	widget_buttoneditor->on_press.callback = switch_bool;
	widget_buttoneditor->on_press.filter = SDL_MOUSEBUTTONDOWN;
	widget_buttoneditor->on_press.user_data = running;
	widget_buttoneditor->on_press.widget = widget_buttoneditor;
	// --- --- Label switch scene --- ---
	size.x = 10;
	size.y = 10;
	size.h = 80;
	size.w = e->win->surface->w - 200;
	if (!libui_create_label(widget_labeleditor, size, "Editor", font))
	{
		printf("Unable to create the label\n");
		return (-1);
	}
	libui_widgets_add_widget(e->win->widgets_surface, widget_labeleditor, 0,
							 widget_buttoneditor);
	return (0);
}

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
	{
		printf("Unable to load the font\n");
	}
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
