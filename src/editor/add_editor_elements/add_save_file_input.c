/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_save_file_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:50:13 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/30 13:50:49 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

int	add_save_file_input(t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	t_libui_inputtext_constructor	cons;

	libui_init_inputtext_constructor(&cons);
	cons.text = editor_interface->save_file_name;
	cons.text_max_len = 20;
	cons.font_color = (SDL_Color){0, 0, 0, 0};
	cons.font = editor_interface->font;
	cons.parent = &editor_interface->editor_container;
	cons.rect = (SDL_Rect){.x = 120, .y = 5, .w = 200, .h = 20};
	cons.label_rect = (SDL_Rect){.x = 0, .y = 0, .w = 200, .h = 20};
	cons.ws = ws;
	if (!libui_create_inputtext(&(editor_interface->input_save_file), &cons))
	{
		printf("create inputtext  a fail\n");
		return (-1);
	}
	return (0);
}
